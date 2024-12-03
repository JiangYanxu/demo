cmake_minimum_required(VERSION 3.15)
project(static_lib DESCRIPTION "test cmake" LANGUAGES CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES CONFIGURE_DEPENDS inc/*.hpp src/*.cpp)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
set_target_properties(${PROJECT_NAME} PROPERTIES 
    PUBLIC_HEADER "inc/sl_public.hpp"
    PRIVATE_HEADER "inc/sl_private.hpp")

install(TARGETS ${PROJECT_NAME}
    PUBLIC_HEADER
    PRIVATE_HEADER
        DESTINATION include_internal
)