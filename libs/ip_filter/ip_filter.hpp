#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class IpFilter {
private:
  std::istream &istream;
  std::vector<uint32_t> addresses;
  std::vector<uint32_t> filtered_addresses;
  bool filtered_valid = false;

public:
  enum class Order { Accending, Descending };
  IpFilter(std::istream &istream);

  void get_data(void);
  void sort(Order order);
  void filter_by_val(uint8_t val,
                     const std::vector<uint8_t> &octets = {0, 1, 2, 3});
  void reset(void);
  void print_sorted(std::ostream &ostream);
  void print_filtered(std::ostream &ostream);
};
