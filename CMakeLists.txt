cmake_minimum_required(VERSION 3.15)
project(demo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.runtime)
set(J_PC_NAME $ENV{J_PC_NAME})
# set(CMAKE_VERBOSE_MAKEFILE ON)

if(${J_PC_NAME} STREQUAL "HXZBook_HyperV_Ubuntu2204")
    message(STATUS "Project on *${J_PC_NAME}*")
    list(APPEND CMAKE_PREFIX_PATH "/home/jiangyx/Qt/5.15.2/gcc_64")
elseif (${J_PC_NAME} STREQUAL "HXZBook")
    message(STATUS "Project on *${J_PC_NAME}*")
    list(APPEND CMAKE_PREFIX_PATH "D:/Qt/5.15.2/mingw81_64")
else()
    message(FATAL_ERROR "Unknown PC! *${J_PC_NAME}*")
endif()

include(${CMAKE_SOURCE_DIR}/library/QxOrm_1_5_0/QxOrm.cmake)

# add_subdirectory(cmake_template)
# add_subdirectory(flex_bison_demo)
# add_subdirectory(gloabl_obj_in_static_lib)
# add_subdirectory(design_mode)
# add_subdirectory(cmake_install_demo)

if(EXISTS "${CMAKE_SOURCE_DIR}/library/QxOrm")
# add_subdirectory(library/QxOrm)
add_subdirectory(library/QxOrm/test/qxBlog)
endif()