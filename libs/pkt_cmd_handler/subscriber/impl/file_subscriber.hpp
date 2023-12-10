#ifndef __FILE_SUBSCRIBER__
#define __FILE_SUBSCRIBER__

#include <isubscriber.hpp>

#include <fstream>

class FileSubscriber : public ISubscriber {
private:
  std::string log_file_prefix;
  std::string log_file_postfix;
  std::fstream log_file;

  std::string get_cur_epoch_time_str(void);

public:
  FileSubscriber(std::string &&log_file_prefix = "bulk",
                 std::string &&log_file_postfix = ".log");
  ~FileSubscriber();

  void notify(const std::string &data) override;
};

#endif /* __FILE_SUBSCRIBER__ */
