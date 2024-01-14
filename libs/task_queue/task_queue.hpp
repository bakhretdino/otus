#ifndef __TASK_QUEUE__
#define __TASK_QUEUE__

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T> class TaskQueue {
private:
  TaskQueue() = default;

  TaskQueue(const TaskQueue &) = delete;
  TaskQueue &operator=(const TaskQueue &) = delete;

  std::queue<T> tasks;

public:
  mutable std::mutex mutex;
  std::condition_variable cv;

  static TaskQueue &get_instance();
  void add(const T &task);
  T get();
  size_t size() const;
};

#include <task_queue.ipp>

#endif /* __TASK_QUEUE__ */
