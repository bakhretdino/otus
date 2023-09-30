#include "vector.hpp"

template <typename T, typename Allocator>
void CustomVector<T, Allocator>::push_back(const T &v) {
  if (size == capacity) {
    capacity += 10;
    auto new_data = std::allocator_traits<Allocator>::allocate(alloc, capacity);
    std::uninitialized_copy(data, data + size, new_data);
    std::allocator_traits<Allocator>::deallocate(alloc, data, size);
    data = new_data;
  }
  std::allocator_traits<Allocator>::construct(alloc, data + size, v);
  size++;
}

template <typename T, typename Allocator>
T *CustomVector<T, Allocator>::begin() const {
  return data;
}

template <typename T, typename Allocator>
T *CustomVector<T, Allocator>::end() const {
  return data + size;
}
