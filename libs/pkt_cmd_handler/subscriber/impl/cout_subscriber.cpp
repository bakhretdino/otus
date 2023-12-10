#include <cout_subscriber.hpp>

#include <iostream>

void CoutSubscriber::notify(const std::string &data) {
  std::cout << data << std::endl;
}
