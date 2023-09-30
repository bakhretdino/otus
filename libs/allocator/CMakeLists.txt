add_library(allocator_lib stack_allocator.hpp stack_allocator.ipp)

set_target_properties(allocator_lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(allocator_lib
    PUBLIC
    .
)
