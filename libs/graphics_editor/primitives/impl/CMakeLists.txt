add_library(primitive_impl)

target_sources(primitive_impl PRIVATE
    primitive_base.cpp
    circle.cpp)

target_include_directories(primitive_impl
    PUBLIC
    .
)

target_link_libraries(primitive_impl primitive_iface)
