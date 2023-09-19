#include <algorithm>
#include <sstream>

#include <ip_filter.hpp>

IpFilter::IpFilter(std::ifstream &if_stream) : istream(if_stream) {}

/* return: true if str1 < str2
 *         false if str1 >= str2 */
bool ip_comparator(const std::string &str1, const std::string &str2) {
  std::istringstream stream1(str1);
  std::istringstream stream2(str2);

  for (int i = 0; i < 4; i++) {
    std::string octet1, octet2;
    std::getline(stream1, octet1, '.');
    std::getline(stream2, octet2, '.');
    if (std::stoi(octet1) > std::stoi(octet2)) {
      return false;
    } else if (std::stoi(octet1) < std::stoi(octet2)) {
      return true;
    }
  }

  return false;
}

void IpFilter::filter(IpFilter::Order order) {
  std::string iline;
  while (std::getline(istream, iline)) {
    size_t pos = iline.find('\t');
    if (pos != std::string::npos) {
      lines.emplace_back(iline.substr(0, pos));
    } else {
      lines.emplace_back(iline);
    }
  }

  if (order == Order::Descending) {
    std::sort(lines.begin(), lines.end(),
              [](const std::string &str1, const std::string &str2) {
                return !ip_comparator(str1, str2);
              });
  } else {
    std::sort(lines.begin(), lines.end(), ip_comparator);
  }
}

void IpFilter::print(std::ostream &ostream, std::regex &pattern) {
  for (auto &line : lines) {
    std::smatch matches;
    if (std::regex_search(line, matches, pattern)) {
      ostream << line << std::endl;
    }
  }
}
