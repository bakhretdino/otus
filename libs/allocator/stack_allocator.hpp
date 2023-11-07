#ifndef __STACK_ALLOCATOR_HPP__
#define __STACK_ALLOCATOR_HPP__

#include <cstddef>
#include <cstdint>
#include <memory>

template <typename T, size_t size = 10> class StackAllocator {
private:
  static T pool[size];
  T *used = nullptr; /* Pointer to the end of the used memory */

public:
  using value_type = T;
  StackAllocator() noexcept;
  template <typename U, size_t size_other>
  StackAllocator(const StackAllocator<U, size_other> &) = delete;
  ~StackAllocator() = default;
  T *allocate(size_t n);
  void deallocate(T *, size_t);
  StackAllocator select_on_container_copy_construction() const;

  template <typename U> struct rebind {
    typedef StackAllocator<U, size> other;
  };

private:
  bool ptr_in_pool(T *p);

public:
  template <typename U, size_t size_other>
  constexpr bool operator==(const StackAllocator<U, size_other> &) noexcept;

  template <typename U, size_t size_other>
  constexpr bool operator!=(const StackAllocator<U, size_other> &) noexcept;

  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::false_type;
};

template <typename T, size_t size> T StackAllocator<T, size>::pool[size]{};

#include "stack_allocator.ipp"

#endif /* __STACK_ALLOCATOR_HPP__ */
