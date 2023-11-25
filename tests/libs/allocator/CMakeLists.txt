add_executable(allocator_test allocator_test.cpp)

target_include_directories(allocator_test
    PRIVATE
    .
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(allocator_test PRIVATE allocator_lib ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

include_directories(${GTEST_INCLUDE_DIRS})

add_test(allocator_test allocator_test)
