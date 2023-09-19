#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

class IpFilter {
private:
  std::ifstream &istream;
  std::vector<std::string> lines;

public:
  enum class Order { Accending, Descending };

  IpFilter(std::ifstream &if_stream);

  void filter(Order order);
  void print(std::ostream &ostream, std::regex &pattern);
};
