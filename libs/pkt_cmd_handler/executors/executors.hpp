#ifndef __EXECUTORS__
#define __EXECUTORS__

#include <task_queue.hpp>

#include <mutex>

namespace Executors {
extern std::once_flag call_once_f;
void log_execute(TaskQueue<std::string> &log_queue);
void file_execute(TaskQueue<std::pair<std::string, std::string>> &file_queue);
void start(TaskQueue<std::string> &log_queue,
           TaskQueue<std::pair<std::string, std::string>> &file_queue);
} // namespace Executors

#endif /* __EXECUTORS__ */
