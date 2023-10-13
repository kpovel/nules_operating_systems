#include <iostream>
#include <vector>
#include <numeric>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <cstring>
#include <chrono>

unsigned short checksum(void *b, int len) {
    unsigned short *buf = (unsigned short *)b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }

    if (len == 1) {
        sum += *(unsigned char *)buf;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

bool ping(const std::string &address, std::vector<double> &rtts) {
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = 0;
    sa.sin_addr.s_addr = inet_addr(address.c_str());

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        std::cerr << "Could not create socket\n";
        return false;
    }

    char packet[sizeof(struct icmp) + 32];
    struct icmp *icmp_header = (struct icmp *)packet;
    icmp_header->icmp_type = ICMP_ECHO;
    icmp_header->icmp_code = 0;
    icmp_header->icmp_id = 0;
    icmp_header->icmp_seq = 1;
    icmp_header->icmp_cksum = 0;
    icmp_header->icmp_cksum = checksum(packet, sizeof(packet));

    auto start_time = std::chrono::high_resolution_clock::now();
    if (sendto(sock, packet, sizeof(packet), 0, (struct sockaddr *)&sa, sizeof(sa)) <= 0) {
        std::cerr << "Failed to send packet\n";
        return false;
    }

    char buffer[1024];
    if (recv(sock, buffer, sizeof(buffer), 0) <= 0) {
      std::cerr << "Failed to receive response\n";
      close(sock);
      return false;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    double duration_ms = duration / 1000.0;

    rtts.push_back(duration_ms);

    std::cout << "64 bytes from " << address << ": icmp_seq=" << icmp_header->icmp_seq;
    std::cout << " ttl=64 time=" << duration_ms << " ms\n";
    close(sock);
    return true;
}

void display_summary(int transmitted, int received, const std::vector<double> &rtts) {
    std::cout << "\n--- " << "127.0.0.1" << " ping statistics ---\n";
    std::cout << transmitted << " packets transmitted, " << received << " packets received, ";
    std::cout << ((transmitted - received) * 100) / transmitted << "% packet loss\n";

    if (!rtts.empty()) {
        double min_rtt = *std::min_element(rtts.begin(), rtts.end());
        double max_rtt = *std::max_element(rtts.begin(), rtts.end());
        double avg_rtt = std::accumulate(rtts.begin(), rtts.end(), 0.0) / rtts.size();

        std::cout << "round-trip min/avg/max = " << min_rtt << "/" << avg_rtt << "/" << max_rtt << " ms\n";
    }
}

int main() {
    std::string ip = "127.0.0.1";
    std::vector<double> rtts;
    int transmitted = 0;
    int received = 0;

    for (int i = 0; i < 4; ++i) {
        ++transmitted;
        if (ping(ip, rtts)) {
            ++received;
        }
        sleep(1);
    }

    display_summary(transmitted, received, rtts);

    return 0;
}

