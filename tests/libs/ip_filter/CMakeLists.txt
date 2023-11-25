add_executable(ip_filter_test ip_filter_test.cpp)

add_custom_command(
    TARGET ip_filter_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/tests/libs/ip_filter/ip_filter.tsv
    ${CMAKE_BINARY_DIR}/tests/libs/ip_filter/ip_filter.tsv
)

target_include_directories(ip_filter_test
    PRIVATE
    .
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(ip_filter_test ip_filter_lib ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

include_directories(${GTEST_INCLUDE_DIRS})

add_test(ip_filter_test ip_filter_test)
