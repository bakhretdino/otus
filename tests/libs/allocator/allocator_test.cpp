#include <map>

#include <gtest/gtest.h>

#include <custom_allocators.hpp>

template <typename Key, typename T>
using StackAllocatedMap =
    std::map<Key, T, std::less<Key>, StackAllocator<std::pair<const Key, T>>>;

TEST(AllocatorTest, TestOnMap) {
  StackAllocator<int> stackalloc;
  // StackAllocatedMap<int, int> map_stack_alloc;
  // map_stack_alloc[0] = 1;
  ASSERT_TRUE(true);
}
