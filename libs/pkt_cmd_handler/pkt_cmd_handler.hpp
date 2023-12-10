#ifndef __PKT_CMD_HANDLER__
#define __PKT_CMD_HANDLER__

#include <isubscriber.hpp>

#include <memory>
#include <string>
#include <vector>

class PktCmdHandler {
private:
  enum class State { Entry, Ordinary, DynamicBlock, Finish };

  std::vector<std::shared_ptr<ISubscriber>> subs;
  std::vector<std::string> cmd_pkt;
  State state = State::Entry;
  int pkt_size;
  const std::string start_delim;
  const std::string stop_delim;
  int recv_cmd_cnt = 0;
  int recv_start_delim_cnt = 0;
  int recv_stop_delim_cnt = 0;

  void print_block();

  /* state handlers */
  void entry();
  void ordinary_block();
  void dynamic_block();
  void finish();

  void add_subscriber(std::unique_ptr<ISubscriber> sub);
  void remove_subscriber(std::unique_ptr<ISubscriber> sub);

public:
  PktCmdHandler(int pkt_size, std::string &&start_delim = "{",
                std::string &&stop_delim = "}");
  ~PktCmdHandler() = default;

  void run();
  void loop();
};

#endif /* __PKT_CMD_HANDLER__ */
