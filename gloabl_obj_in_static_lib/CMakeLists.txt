cmake_minimum_required(VERSION 3.27)
project(global_obj_in_static_lib DESCRIPTION "研究静态库的全局对象" LANGUAGES C CXX)

find_package(Qt5 COMPONENTS Core)

add_library(${PROJECT_NAME}_static_lib STATIC)
target_sources(${PROJECT_NAME}_static_lib PRIVATE static_lib.hpp static_lib.cpp)
target_include_directories(${PROJECT_NAME}_static_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_static_lib PUBLIC Qt5::Core)

add_library(${PROJECT_NAME}_dynamic_lib_a SHARED)
target_sources(${PROJECT_NAME}_dynamic_lib_a PRIVATE dynamic_lib_a.hpp dynamic_lib_a.cpp)
target_compile_definitions(${PROJECT_NAME}_dynamic_lib_a PRIVATE A_LIBRARY)
target_link_libraries(${PROJECT_NAME}_dynamic_lib_a PRIVATE ${PROJECT_NAME}_static_lib)

add_library(${PROJECT_NAME}_dynamic_lib_b SHARED)
target_sources(${PROJECT_NAME}_dynamic_lib_b PRIVATE dynamic_lib_b.hpp dynamic_lib_b.cpp)
target_link_libraries(${PROJECT_NAME}_dynamic_lib_b PRIVATE ${PROJECT_NAME}_static_lib)
target_compile_definitions(${PROJECT_NAME}_dynamic_lib_b PRIVATE B_LIBRARY)

add_executable(${PROJECT_NAME}_main main.cpp)
target_link_libraries(${PROJECT_NAME}_main PUBLIC Qt5::Core)
target_include_directories(${PROJECT_NAME}_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_main PRIVATE ${PROJECT_NAME}_dynamic_lib_a ${PROJECT_NAME}_dynamic_lib_b)