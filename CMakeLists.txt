cmake_minimum_required(VERSION 3.20)

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

# Tests
enable_testing()
add_executable(ip_filter_app apps/hw2_ip_filter.cpp)
target_link_libraries(ip_filter_app PUBLIC ip_filter_lib)

find_package(GTest REQUIRED)

add_subdirectory(tests)

# Pack generator
install(TARGETS ip_filter_app RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT bakhretdino@mail.ru)

include(CPack)
