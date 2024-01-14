template <typename T> TaskQueue<T> &TaskQueue<T>::get_instance() {
  static TaskQueue<T> instance;
  return instance;
}

template <typename T> void TaskQueue<T>::add(const T &task) {
  std::lock_guard<std::mutex> lock(mutex);
  tasks.push(task);
  cv.notify_one();
}

template <typename T> T TaskQueue<T>::get() {
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this] { return !tasks.empty(); });

  T task = tasks.front();
  tasks.pop();
  return task;
}

template <typename T> size_t TaskQueue<T>::size() const {
  std::lock_guard<std::mutex> lock(mutex);
  return tasks.size();
}
