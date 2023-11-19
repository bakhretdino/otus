#ifndef __PKT_CMD_HANDLER__
#define __PKT_CMD_HANDLER__

#include <fstream>
#include <string>

class PktCmdHandler {
private:
  enum class State { Entry, Ordinary, DynamicBlock, Finish };

  State state = State::Entry;
  int pkt_size;
  std::string log_file_prefix;
  std::string log_file_postfix;
  const std::string start_delim;
  const std::string stop_delim;
  std::fstream cur_log_file;
  int recv_cmd_cnt = 0;
  int recv_start_delim_cnt = 0;
  int recv_stop_delim_cnt = 0;

  std::string get_cur_epoch_time_str(void);

  /* state handlers */
  void entry();
  void ordinary_block();
  void dynamic_block();
  void finish();
  void print_block();

public:
  PktCmdHandler(int pkt_size, std::string &&log_file_prefix = "bulk",
                std::string &&log_file_postfix = ".log",
                std::string &&start_delim = "{",
                std::string &&stop_delim = "}");
  ~PktCmdHandler();
  void loop();
};

#endif /* __PKT_CMD_HANDLER__ */
