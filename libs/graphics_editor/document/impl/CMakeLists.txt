add_library(document_impl)
target_sources(document_impl PRIVATE
    document_raw.cpp
)
target_include_directories(document_impl PUBLIC
    .
)
target_link_libraries(document_impl PRIVATE document_iface primitive_impl)
