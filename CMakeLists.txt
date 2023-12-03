cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAJOR_VERSION "0" CACHE INTERNAL "Major version")
set(MINOR_VERSION "0" CACHE INTERNAL "Minor version")
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

project(playground VERSION ${PROJECT_VERSION})

set(MY_BUILD_DIR "build")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/${MY_BUILD_DIR})

configure_file(
    config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_subdirectory(libs)

add_executable(ip_filter_app apps/hw2_ip_filter.cpp)
target_link_libraries(ip_filter_app PUBLIC ip_filter_lib)

add_executable(allocators_app apps/hw3_allocators.cpp)
target_link_libraries(allocators_app custom_containers_lib allocator_lib)

add_executable(ip_print apps/hw4_ip_printer.cpp)
target_link_libraries(ip_print ip_printer_lib)

add_executable(grapic_editor apps/hw5_graphics_editor.cpp)
target_link_libraries(grapic_editor primitive_iface primitive_impl document_factory document_iface)

add_executable(sparse_matrix_app apps/hw6_sparse_matrix.cpp)
target_link_libraries(sparse_matrix_app sparse_matrix)

add_executable(bulk apps/hw7_pkt_cmd_handler.cpp)
target_link_libraries(bulk pkt_cmd_handler)

# Tests
enable_testing()

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(tests)

# Pack generator
install(TARGETS ip_print RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT bakhretdino@mail.ru)

include(CPack)
