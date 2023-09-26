#include <iostream>
#include <ip_filter.hpp>

int main() {
  auto ip_filter = IpFilter(std::cin);
  ip_filter.get_data();
  ip_filter.sort(IpFilter::Order::Descending);
  ip_filter.print_sorted(std::cout);
  ip_filter.filter_by_val(1, {0});
  ip_filter.print_filtered(std::cout);
  ip_filter.reset();
  ip_filter.filter_by_val(46, {0});
  ip_filter.filter_by_val(70, {1});
  ip_filter.print_filtered(std::cout);
  ip_filter.reset();
  ip_filter.filter_by_val(46);
  ip_filter.print_filtered(std::cout);
  ip_filter.reset();

  return 0;
}
