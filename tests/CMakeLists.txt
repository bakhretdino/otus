add_executable(hello_test hello_test.cpp)

target_include_directories(hello_test
    PRIVATE
    .
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(hello_test version_lib ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

include_directories(${GTEST_INCLUDE_DIRS})


add_test(hello_test hello_test)
