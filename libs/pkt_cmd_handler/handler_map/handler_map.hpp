// HandlerMap.h
#ifndef __HANDLER_MAP__
#define __HANDLER_MAP__

#include <memory>
#include <type_traits>
#include <unordered_map>

template <typename T> class HandlerMap {
private:
  using handle_type = void *; // Use void* as the identifier
  using obj_ptr = std::shared_ptr<T>;

  std::unordered_map<handle_type, obj_ptr> handler_threads;

  HandlerMap() = default;
  ~HandlerMap() = default;
  HandlerMap(const HandlerMap &) = delete;
  HandlerMap &operator=(const HandlerMap &) = delete;

public:
  static HandlerMap<T> &get_instance() {
    static HandlerMap<T> instance;
    return instance;
  }

  handle_type add(obj_ptr obj, handle_type handle) {
    auto result = handler_threads.insert({handle, obj});
    if (result.second) {
      return handle;
    }

    return result.first->first;
  }

  obj_ptr get(handle_type handle) {
    auto it = handler_threads.find(handle);
    return (it != handler_threads.end()) ? it->second : nullptr;
  }

  handle_type find(handle_type handle) {
    auto it = handler_threads.find(handle);
    return (it != handler_threads.end()) ? it->first : nullptr;
  }

  void remove(handle_type handle) { handler_threads.erase(handle); }
};

#endif /* __HANDLER_MAP__ */
