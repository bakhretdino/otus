add_library(executors STATIC executors.cpp)
target_include_directories(executors INTERFACE ./)
target_link_libraries(executors PUBLIC task_queue)
