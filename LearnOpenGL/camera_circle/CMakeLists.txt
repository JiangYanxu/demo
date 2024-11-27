cmake_minimum_required(VERSION 3.22)
project(camera_circle LANGUAGES C CXX)

set(VERTEX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shader.vs)
set(FRAGMENT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shader.fs)
set(IMAGES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../images)
configure_file(config.hpp.in config.hpp @ONLY)

file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw OpenGL::GL common)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:LIBCMTD")
endif()
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PFPA}/glew/bin/glew32d.dll ${RUNTIME_PATH}
#     WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})