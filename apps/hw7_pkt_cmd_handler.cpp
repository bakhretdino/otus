#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <pkt_cmd_handler.hpp>

int main(int argc, char *argv[]) {
  if ((argc != 2) || (argv[1] == nullptr) ||
      std::any_of(argv[1], argv[1] + std::strlen(argv[1]),
                  [](char c) { return !std::isdigit(c); })) {
    std::cout << "Provide a single numeric argument\n";
    return 1;
  }

  int pkt_size = std::stoi(argv[1]);

  PktCmdHandler handler(pkt_size);

  handler.loop();

  return 0;
}
