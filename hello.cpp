#include <iostream>
#include <version.hpp>

int main() {
  std::cout << "build " << get_ver_patch() << std::endl;
  std::cout << "Hello, World!\n";
  return 0;
}
