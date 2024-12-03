cmake_minimum_required(VERSION 3.15)
project(cmake_install_demo DESCRIPTION "test cmake" LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core static_lib dynamic_lib)

install(TARGETS ${PROJECT_NAME})