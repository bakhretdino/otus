template <typename T, size_t size>
StackAllocator<T, size>::StackAllocator() noexcept : used(pool) {}

template <typename T, size_t size>
template <typename U, size_t size_other>
StackAllocator<T, size>::StackAllocator(
    const StackAllocator<U, size_other> &other) noexcept {
  pool = other.pool;
  used = other.used;
}

template <typename T, size_t size>
StackAllocator<T, size>
StackAllocator<T, size>::select_on_container_copy_construction() const {
  return StackAllocator<T, size>();
}

template <typename T, size_t size>
T *StackAllocator<T, size>::allocate(size_t n) {
  /* Allocate on stack if no pool overflow */
  if (pool + size >= used + n) {
    auto ret = used;
    used += n;
    return ret;
  } else {
    throw std::bad_alloc();
  }
}

template <typename T, size_t size> void StackAllocator<T, size>::deallocate(T *p, size_t n) {
  if (ptr_in_pool(p)) {
    used -= n;
  }
}

template <typename T, size_t size> bool StackAllocator<T, size>::ptr_in_pool(T *p) {
  return (p >= pool) && (p <= pool + size);
}

template <typename T, size_t size>
template <typename U, size_t size_other>
constexpr bool
StackAllocator<T, size>::operator==(const StackAllocator<U, size_other> &other) noexcept {
  return this->pool == other.pool;
}

template <typename T, size_t size>
template <typename U, size_t size_other>
constexpr bool StackAllocator<T, size>::operator!=(
    const StackAllocator<U, size_other> &other) noexcept {
  return this->pool != other.pool;
}
