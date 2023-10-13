#include <iostream>
#include <string>

using namespace std;
void ping(string adr) {
  string ping = "ping " + adr;
  char *a = new char[ping.size() + 1];
  a[ping.size()] = 0;
  memcpy(a, ping.c_str(), ping.size());
  system(a);
}

int main() {
  string ip = "127.0.0.1";
  ping(ip);
  system("pause");
  return 0;
}

