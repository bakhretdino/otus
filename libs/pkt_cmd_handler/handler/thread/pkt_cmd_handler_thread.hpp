#ifndef __PKT_CMD_HANDLER_THREAD__
#define __PKT_CMD_HANDLER_THREAD__

#include <pkt_cmd_handler.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class PktCmdHandlerThread {
private:
  std::thread thread;
  std::shared_ptr<PktCmdHandler> handler;
  std::queue<std::string> queue;
  std::mutex mutex;
  std::condition_variable cv;
  bool stop_flag = false;

  void run();

public:
  PktCmdHandlerThread(std::shared_ptr<PktCmdHandler> handler);

  void execute(const char *data, size_t size);

  void stop();
};

#endif /* __PKT_CMD_HANDLER_THREAD__ */
