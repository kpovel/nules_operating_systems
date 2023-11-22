// g++ -std=c++17 main.cpp -o ./target/main && ./target/main

#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

std::string extractRequestBody(const std::string &request) {
  size_t headersEnd = request.find("\r\n\r\n");
  if (headersEnd == std::string::npos) {
    headersEnd = request.find("\n\n");
    if (headersEnd == std::string::npos) {
      return "";
    }
  }

  return request.substr(headersEnd + 4);
}

int countA(const std::string &str) {
  int count = 0;
  for (char c : str) {
    if (c == 'a' || c == 'A') {
      count++;
    }
  }

  return count;
}

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Define the socket type
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(42069);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening at port " << htons(address.sin_port) << std::endl;

  while (true) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    // Read request
    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);
    std::string request(buffer);

    if (request.find("POST /task1 ") != std::string::npos) {
      std::string requestBody = extractRequestBody(request);
      std::cout << "Request body: " << requestBody << std::endl;

      std::string response = "HTTP/1.1 200 OK\n"
                             "Content-Type: text/plain\n"
                             "Connection: close\n\n";
      write(new_socket, response.c_str(), response.size());
    } else if (request.find("POST /task2 ") != std::string::npos) {
      std::string requestBody = extractRequestBody(request);
      int numberOfA = countA(requestBody);

      std::string response = "HTTP/1.1 200 OK\n"
                             "Content-Type: text/plain\n"
                             "Connection: close\n\n"
                             "Number of 'a' letters in the request body: " +
                             std::to_string(numberOfA);

      write(new_socket, response.c_str(), response.size());
    } else {
      std::string response = "HTTP/1.1 404 Not Found\nContent-Type: "
                             "text/plain\nContent-Length: 13\n\n404 Not Found";
      write(new_socket, response.c_str(), response.size());
    }

    close(new_socket);
  }

  return 0;
}

