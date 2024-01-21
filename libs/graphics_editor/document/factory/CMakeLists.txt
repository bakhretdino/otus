add_library(document_factory)
target_sources(document_factory PRIVATE
    document_factory.cpp
)
target_include_directories(document_factory
    PUBLIC
    .
)
target_link_libraries(document_factory PUBLIC document_iface document_impl)
