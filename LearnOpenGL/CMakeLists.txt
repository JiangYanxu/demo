cmake_minimum_required(VERSION 3.27)
project(Programs VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17) # 默认 MingW:17 MSVC:14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17) # 默认 MingW:17 MSVC:99
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.runtime)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
    message(STATUS 
        "======== No build type is specified, used default: ${CMAKE_BUILD_TYPE}. "
        "-DCMAKE_BUILD_TYPE:STRING=[Debug|Release|RelWithDebInfo|MinSizeRel|<custom>]")
endif()

message(STATUS "======== CMAKE_BUILD_TYPE       : ${CMAKE_BUILD_TYPE}")
message(STATUS "======== CMAKE_SYSTEM           : ${CMAKE_SYSTEM}")
message(STATUS "======== CMAKE_C_COMPILER_ID    : ${CMAKE_C_COMPILER_ID}")
message(STATUS "======== CMAKE_CXX_COMPILER_ID  : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "======== CMAKE_SIZEOF_VOID_P    : ${CMAKE_SIZEOF_VOID_P} Byte")
message(STATUS "======== CMAKE_C_COMPILER       : ${CMAKE_C_COMPILER}")
message(STATUS "======== CMAKE_CXX_COMPILER     : ${CMAKE_CXX_COMPILER}")
# message(STATUS "======== System PATH            : $ENV{PATH}")

# cmake -G "Visual Studio 17 2022" --system-information "VS 17 2022 System Information.txt"

set (RUNTIME_PATH ".")
if (MSVC)
    set(RUNTIME_PATH "./${CMAKE_BUILD_TYPE}/")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

set(PFPA "D:/Program Files")
list(APPEND CMAKE_PREFIX_PATH ${PFPA}/GLFW ${PFPA}/glm ${PFPA}/soil2 ${PFPA}/glew)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(soil2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(glad)
add_subdirectory(common)
# add_subdirectory(hello_world)
# add_subdirectory(hello_triangle)
# add_subdirectory(hello_square)
# add_subdirectory(getting_started_shaders)
# add_subdirectory(colored_triangle)
# add_subdirectory(class_shader)
# add_subdirectory(textures)
# add_subdirectory(happy_box)
# add_subdirectory(happy_box_glm)
# add_subdirectory(coordinate_systems)
# add_subdirectory(coordinate_systems_depth)
# add_subdirectory(coordinate_systems_multiple)
add_subdirectory(camera_circle)

add_subdirectory(temp_for_matrix)