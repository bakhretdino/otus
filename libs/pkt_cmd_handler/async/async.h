#ifndef __ASYNC__
#define __ASYNC__

#include <cstddef>

namespace async {

using handle_t = void *;

handle_t connect(std::size_t bulk);
void receive(handle_t handle, const char *data, std::size_t size);
void disconnect(handle_t handle);
} // namespace async

#endif /* __ASYNC__ */
