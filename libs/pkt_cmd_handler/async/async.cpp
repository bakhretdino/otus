#include "async.h"
#include <executors.hpp>
#include <handler_map.hpp>
#include <pkt_cmd_handler_thread.hpp>
#include <task_queue.hpp>

namespace async {

handle_t connect(std::size_t bulk) {
  /* Create task queues */
  auto &log_queue = TaskQueue<std::string>::get_instance();
  auto &file_queue =
      TaskQueue<std::pair<std::string, std::string>>::get_instance();

  /* Create executors' tasks once */
  std::call_once(Executors::call_once_f, &Executors::start, log_queue,
                 file_queue);

  auto &handler_thread_map = HandlerMap<PktCmdHandlerThread>::get_instance();
  auto handle = handler_thread_map.find(reinterpret_cast<void *>(bulk));

  if (handle == nullptr) {
    /* Create a new handle and add the corresponding handler to the map */
    handle = handler_thread_map.add(
        std::make_shared<PktCmdHandlerThread>(
            std::make_shared<PktCmdHandler>(bulk, log_queue, file_queue)),
        reinterpret_cast<void *>(bulk));
  }

  return handle;
}

void receive(handle_t handle, const char *data, std::size_t size) {
  auto &handler_thread_map = HandlerMap<PktCmdHandlerThread>::get_instance();
  auto handler_thread = handler_thread_map.get(handle);
  if (handler_thread == nullptr) {
    return;
  } else {
    handler_thread->execute(data, size);
  }
}

void disconnect(handle_t handle) {
  auto &handler_thread_map = HandlerMap<PktCmdHandlerThread>::get_instance();
  auto ptr = handler_thread_map.get(handle);
  if (ptr == nullptr) {
    return;
  } else {
    ptr->stop();
    handler_thread_map.remove(handle);
  }
}

} // namespace async
