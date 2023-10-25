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

add_executable(grapic_editor apps/hw5_graphics_editor.cpp)
target_link_libraries(grapic_editor primitive_iface primitive_impl document_factory document_iface)

# Tests
enable_testing()

find_package(GTest REQUIRED)

add_subdirectory(tests)

# Pack generator
install(TARGETS grapic_editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT bakhretdino@mail.ru)

include(CPack)
