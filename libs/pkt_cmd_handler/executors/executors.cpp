#include "executors.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

namespace Executors {
std::once_flag call_once_f;
};

void Executors::log_execute(TaskQueue<std::string> &log_queue) {
  auto doer = [&](std::unique_lock<std::mutex> &lock) {
    auto str = log_queue.get();
    lock.unlock();
    std::string temp = (str);
    std::cout << temp;
  };

  while (1) {
    std::unique_lock<std::mutex> lock(log_queue.mutex);
    if (log_queue.size() > 0) {
      doer(std::ref(lock));
    } else {
      log_queue.cv.wait(lock, [&log_queue] { return (log_queue.size() > 0); });
      doer(std::ref(lock));
    }
  }
}

void Executors::file_execute(
    TaskQueue<std::pair<std::string, std::string>> &file_queue) {
  auto doer = [&](std::unique_lock<std::mutex> &lock) {
    auto pair = file_queue.get();
    bool need_notify = (file_queue.size() > 0);
    lock.unlock();
    if (need_notify) {
      file_queue.cv.notify_one(); /* Notify another file logger thread */
    }
    std::fstream stream;
    std::thread::id id = std::this_thread::get_id();
    std::stringstream namestream;
    namestream << pair.second << "_thread" << id << ".log";
    std::string fileName = namestream.str();
    stream.open(fileName, std::ios_base::out);
    stream << pair.first;
    stream.close();
  };

  for (;;) {
    std::unique_lock<std::mutex> lock(file_queue.mutex);
    if (file_queue.size() > 0) {
      doer(std::ref(lock));
    } else {
      file_queue.cv.wait(lock,
                         [&file_queue] { return (file_queue.size() > 0); });
      doer(std::ref(lock));
    }
  }
}

/* Run threads for logging (one for terminal and 2 for logging to file) */
void Executors::start(
    TaskQueue<std::string> &log_queue,
    TaskQueue<std::pair<std::string, std::string>> &file_queue) {
  auto log_thread = std::thread(log_execute, std::ref(log_queue));

  auto file_thread1 = std::thread(file_execute, std::ref(file_queue));
  auto file_thread2 = std::thread(file_execute, std::ref(file_queue));

  log_thread.detach();
  file_thread1.detach();
  file_thread2.detach();
}
