cmake_minimum_required(VERSION 3.15)
project(cmake_template DESCRIPTION "A template project using CMake" LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
