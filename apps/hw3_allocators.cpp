#include <iostream>
#include <map>

#include <allocators.hpp>
#include <vector.hpp>
#include <vector>

int factorial(unsigned int n) {
  if (n == 0 || n == 1)
    return 1;
  return n * factorial(n - 1);
}

template <typename Key, typename T>
using StackAllocatedMap =
    std::map<Key, T, std::less<Key>, StackAllocator<std::pair<const Key, T>>>;

int main(void) {
  /* Default allocator for STL map */
  std::map<int, int> map;
  for (int i = 0; i < 10; i++) {
    map[i] = factorial(i);
  }

  std::cout << "Default allocator STD map:\nKey\tValue" << std::endl;
  for (auto [k, v] : map) {
    std::cout << k << "\t" << v << std::endl;
  }

  /* Custom allocator for std::map */
  StackAllocatedMap<int, int> map_stack_alloc;
  for (int i = 0; i < 10; i++) {
    map_stack_alloc[i] = factorial(i);
  }

  std::cout << "\n\nStack allocated STL map:\nKey\tValue" << std::endl;
  for (auto [k, v] : map_stack_alloc) {
    std::cout << k << "\t" << v << std::endl;
  }

  /* Default allocator for CustomVector */
  CustomVector<int> custom_vector;
  for (int i = 0; i < 10; i++) {
    custom_vector.push_back(factorial(i));
  }

  std::cout << "\n\nStack allocated CustomVector:\nValue" << std::endl;
  for (auto v : custom_vector) {
    std::cout << v << std::endl;
  }

  /* Custom allocator for CustomVector */
  CustomVector<int, StackAllocator<int, 20>> custom_vector_stack_alloc;
  for (int i = 0; i < 10; i++) {
    custom_vector_stack_alloc.push_back(factorial(i));
  }

  std::cout << "\n\nStack allocated CustomVector:\nValue" << std::endl;
  for (auto v : custom_vector_stack_alloc) {
    std::cout << v << std::endl;
  }

  /* Custom allocator for std::vector */
  std::vector<int, StackAllocator<int>> std_vector_stack_alloc;
  /* If not reserving, stack allocator doesn't work correctly.
   * A research should be performed */
  std_vector_stack_alloc.reserve(10);
  for (int i = 0; i < 10; i++) {
    std_vector_stack_alloc.push_back(factorial(i));
  }

  std::cout << "\n\nStack allocated std::vector:\nValue" << std::endl;
  for (auto v : std_vector_stack_alloc) {
    std::cout << v << std::endl;
  }

  /* CustomVector destructor check */
  {
    CustomVector<int> ann;
    ann.push_back(42);
    auto bob = ann;
  }

  return 0;
}
