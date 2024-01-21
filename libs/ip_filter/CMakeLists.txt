add_library(ip_filter_lib ip_filter.cpp)

target_include_directories(ip_filter_lib
    PUBLIC
    .
    ${CMAKE_BINARY_DIR}
)
