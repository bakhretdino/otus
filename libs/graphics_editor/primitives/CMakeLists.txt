add_library(primitive_iface INTERFACE)

target_include_directories(primitive_iface
    INTERFACE
    .
    properties/
)

add_subdirectory(impl)
