cmake_minimum_required(VERSION 3.27)
project(DesignMode DESCRIPTION "设计模式的示例" LANGUAGES C CXX)

add_executable(${PROJECT_NAME}_Command command/command_demo.cpp)

