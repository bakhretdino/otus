add_library(pkt_cmd_handler STATIC pkt_cmd_handler.cpp)
target_include_directories(pkt_cmd_handler PUBLIC ./)
target_link_libraries(pkt_cmd_handler PUBLIC subscriber_factory)

add_subdirectory(subscriber)
