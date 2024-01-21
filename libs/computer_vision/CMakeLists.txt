add_library(cv_classifier_iface INTERFACE)

target_include_directories(cv_classifier_iface INTERFACE .)

add_subdirectory(mlp)
