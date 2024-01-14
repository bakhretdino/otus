add_library(task_queue task_queue.hpp)
target_include_directories(task_queue PUBLIC .)
set_target_properties(task_queue PROPERTIES LINKER_LANGUAGE CXX)
