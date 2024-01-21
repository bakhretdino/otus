add_library(version_lib version.cpp)

target_include_directories(version_lib
    PUBLIC
    .
    ${CMAKE_BINARY_DIR}
)
