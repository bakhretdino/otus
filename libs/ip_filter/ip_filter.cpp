#include <algorithm>
#include <sstream>

#include <ip_filter.hpp>

IpFilter::IpFilter(std::istream &istream) : istream(istream) {}

uint32_t ipstr2hex(const std::string &str) {
  size_t pos = 0;
  uint32_t result = 0;

  for (int i = 0; i < 4; ++i) {
    size_t nextPos = str.find('.', pos);
    result = (result << 8) | std::atoi(str.substr(pos, nextPos - pos).c_str());
    pos = nextPos + 1;
  }

  return result;
}

std::string hex2ipstr(uint32_t ip_hex) {
  char buffer[16];
  std::sprintf(buffer, "%u.%u.%u.%u", (ip_hex >> 24) & 0xFF,
               (ip_hex >> 16) & 0xFF, (ip_hex >> 8) & 0xFF, ip_hex & 0xFF);
  return buffer;
}

void IpFilter::get_data(void) {
  std::string iline;
  while (std::getline(istream, iline)) {
    if (iline.empty()) {
      break;
    }
    size_t pos = iline.find('\t');
    if (pos != std::string::npos) {
      iline.erase(pos);
    }
    addresses.emplace_back(ipstr2hex(iline));
  }
}

void IpFilter::sort(Order order) {
  if (order == Order::Descending) {
    std::sort(addresses.begin(), addresses.end(), std::greater<uint32_t>());
  } else {
    std::sort(addresses.begin(), addresses.end());
  }
}

void IpFilter::filter_by_val(uint8_t val, const std::vector<uint8_t> &octets) {
  auto &source_set = filtered_valid ? filtered_addresses : addresses;
  std::vector<uint32_t> tmp_set;
  for (auto addr : source_set) {
    for (uint8_t octet : octets) {
      if ((((addr >> (8 * (3 - octet))) & 0xFF) == val)) {
        tmp_set.emplace_back(addr);
        break;
      }
    }
  }
  filtered_addresses = tmp_set;
  filtered_valid = true;
}

void IpFilter::reset() {
  filtered_addresses.clear();
  filtered_valid = false;
}

void IpFilter::print_sorted(std::ostream &ostream) {
  for (auto addr : addresses) {
    ostream << hex2ipstr(addr) << std::endl;
  }
}

void IpFilter::print_filtered(std::ostream &ostream) {
  for (auto addr : filtered_addresses) {
    ostream << hex2ipstr(addr) << std::endl;
  }
}
