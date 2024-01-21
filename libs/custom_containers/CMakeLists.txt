add_library(custom_containers_lib vector.hpp)

set_target_properties(custom_containers_lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(custom_containers_lib
    PUBLIC
    .
)
