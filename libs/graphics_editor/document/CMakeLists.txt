add_library(document_iface INTERFACE)
target_include_directories(document_iface
    INTERFACE
    .
)
target_link_libraries(document_iface INTERFACE primitive_iface)

add_subdirectory(factory)
add_subdirectory(impl)

add_library(document INTERFACE)
target_link_libraries(document INTERFACE document_iface document_factory document_impl)
