cmake_minimum_required(VERSION 3.15)
project(dynamic_lib DESCRIPTION "test cmake" LANGUAGES CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES CONFIGURE_DEPENDS inc/*.hpp src/*.cpp)

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_DL_LIB)

install(TARGETS ${PROJECT_NAME})