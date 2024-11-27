cmake_minimum_required(VERSION 3.22)
project(colored_triangle LANGUAGES C CXX)

file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw OpenGL::GL glad)
if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:LIBCMTD")
endif()
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PFPA}/glew/bin/glew32d.dll ${RUNTIME_PATH}
#     WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})