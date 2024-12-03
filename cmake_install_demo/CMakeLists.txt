cmake_minimum_required(VERSION 3.15)
project(cmake_install_demo DESCRIPTION "test cmake" LANGUAGES CXX)

include(root.cmake)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_subdirectory(dynamic_lib)
add_subdirectory(static_lib)
add_subdirectory(hello_cmake)
