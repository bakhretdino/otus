#include <fstream>
#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <string>

#include <gtest/gtest.h>
#include <ip_filter.hpp>

void calc_md5sum(const std::string &file_path, std::string &res) {
  std::string command = "md5sum " + file_path + " 2>&1";
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    res = "";
    return; // Handle error
  }

  char buffer[128];
  res = "";
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    res += buffer;
  }

  pclose(pipe);

  /* Trim md5 out of the other rubbish */
  std::size_t pos = res.find(' ');
  if (pos != std::string::npos) {
    res = res.erase(pos);
  }
}

TEST(IpVersionTest, CompareMD5) {
  std::ifstream finput("ip_filter.tsv");
  auto ip_filter = IpFilter(finput);
  ip_filter.filter(IpFilter::Order::Descending);

  std::fstream file("output.txt",
                    std::ios::binary | std::ios::out | std::ios::trunc);

  /* Print result */
  std::regex pattern(".*");
  ip_filter.print(file, pattern);
  /* 1st octet = 1 */
  pattern = "\\b1\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\b";
  ip_filter.print(file, pattern);
  /* 1st octet = 46 && 2nd octet = 70 */
  pattern = "\\b46\\.70\\.[0-9]{1,3}\\.[0-9]{1,3}\\b";
  ip_filter.print(file, pattern);
  /* Any octet = 46 */
  /* pattern = "(?:\\.|^)42(?:\\.|$)"; - if we don't trim lines after tab */
  pattern = "\\b(46|([0-9]{1,3}\\.){3}46)\\b";
  ip_filter.print(file, pattern);
  file.close();

  /* Check MD5 of the file */
  std::string expected_md5sum = "24e7a7b2270daee89c64d3ca5fb3da1a";
  std::string actual_md5sum = "";
  calc_md5sum("output.txt", actual_md5sum);
  ASSERT_EQ(expected_md5sum, actual_md5sum);
}
