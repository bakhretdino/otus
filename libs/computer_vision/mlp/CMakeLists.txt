find_package (Eigen3 3.3 REQUIRED)

add_library(mlp_classifier STATIC mlp_classifier.cpp)
target_include_directories(mlp_classifier PUBLIC ./)
target_link_libraries(mlp_classifier cv_classifier_iface Eigen3::Eigen)
