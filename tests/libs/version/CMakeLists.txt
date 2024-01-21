add_executable(version_test version_test.cpp)

target_include_directories(version_test
    PRIVATE
    .
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(version_test version_lib ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

include_directories(${GTEST_INCLUDE_DIRS})

add_test(version_test version_test)
