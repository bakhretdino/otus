add_library(subscriber_iface INTERFACE)
target_include_directories(subscriber_iface INTERFACE ./)

add_library(subscriber_impl STATIC
    impl/file_subscriber.cpp
    impl/cout_subscriber.cpp # Not used for now
)
target_link_libraries(subscriber_impl PUBLIC subscriber_iface)
target_include_directories(subscriber_impl PUBLIC impl/)

add_library(subscriber_factory STATIC factory/subscriber_factory.cpp)
target_link_libraries(subscriber_factory PUBLIC subscriber_impl)
target_include_directories(subscriber_factory PUBLIC factory/)
