#ifndef __VECTOR__
#define __VECTOR__

#include <memory>

template <typename T, class Allocator = std::allocator<T>> class CustomVector {
private:
  size_t size = 0;
  size_t capacity = 0;
  T *data = nullptr;
  Allocator alloc;

public:
  CustomVector() = default;
  CustomVector(const CustomVector<T, Allocator> &other);
  ~CustomVector();
  void push_back(const T &v);
  T *begin() const;
  T *end() const;
};

#include "vector.ipp"
#endif /* __VECTOR__ */
