#ifndef __PKT_CMD_HANDLER__
#define __PKT_CMD_HANDLER__

// #include <isubscriber.hpp>
#include <task_queue.hpp>

#include <memory>
#include <string>
#include <vector>

class PktCmdHandler {
private:
  enum class State { Entry, Ordinary, DynamicBlock, Finish };

  std::vector<std::string> cmd_pkt;
  State state = State::Entry;
  int pkt_size;
  const std::string start_delim;
  const std::string stop_delim;
  int recv_cmd_cnt = 0;
  int recv_start_delim_cnt = 0;
  int recv_stop_delim_cnt = 0;
  std::string file_timestamp;

  /* Task queues */
  TaskQueue<std::string> &log_queue;
  TaskQueue<std::pair<std::string, std::string>> &file_queue;

  void print_block();

  /* state handlers */
  void entry(const std::string &cmd);
  void ordinary_block(const std::string &cmd);
  void dynamic_block(const std::string &cmd);
  void finish();

  std::string get_cur_epoch_time_str();
  // void add_subscriber(std::unique_ptr<ISubscriber> sub);
  // void remove_subscriber(std::unique_ptr<ISubscriber> sub);

  // void init_subscriber_threads();

public:
  PktCmdHandler(int pkt_size, TaskQueue<std::string> &log_queue,
                TaskQueue<std::pair<std::string, std::string>> &file_queue,
                std::string &&start_delim = "{",
                std::string &&stop_delim = "}");

  ~PktCmdHandler() = default;

  void run(std::string data);
};

#endif /* __PKT_CMD_HANDLER__ */
