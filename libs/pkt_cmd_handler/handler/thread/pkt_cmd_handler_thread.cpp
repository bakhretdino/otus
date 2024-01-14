#include <pkt_cmd_handler_thread.hpp>

#include <cstring>

PktCmdHandlerThread::PktCmdHandlerThread(std::shared_ptr<PktCmdHandler> handler)
    : handler(handler) {
  thread = std::thread([this] { run(); });
  thread.detach();
}

void PktCmdHandlerThread::run() {
  auto func = [&](std::unique_lock<std::mutex> &lock) {
    auto line = std::move(queue.front());
    queue.pop();
    lock.unlock();
    handler.get()->run(line);
  };

  while (true) {
    std::unique_lock<std::mutex> lock(mutex);
    if (queue.size() > 0) {
      func(std::ref(lock));
    } else {
      if (stop_flag) {
        break;
      } else {
        cv.wait(lock, [this] { return (queue.size() > 0); });
        func(std::ref(lock));
      }
    }
  }
}

void PktCmdHandlerThread::execute(const char *data, size_t size) {
  if (stop_flag) {
    return;
  }

  std::string temp;
  if ((size == 1) && (*data == EOF)) {
    temp = "EOF";
  } else {
    temp.assign(data, size);
  }
  std::lock_guard<std::mutex> lock(mutex);
  queue.push(temp);
  cv.notify_one();
}

void PktCmdHandlerThread::stop() { stop_flag = true; }
