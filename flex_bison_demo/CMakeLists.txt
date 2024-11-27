cmake_minimum_required(VERSION 3.15)
project(flex_bison_demo DESCRIPTION "浅尝以下flex与bison")

find_package(BISON)
find_package(FLEX)

if (BISON_FOUND AND FLEX_FOUND)

BISON_TARGET(Parser calc.y ${CMAKE_CURRENT_BINARY_DIR}/calc.tab.c)
FLEX_TARGET(Scanner calc.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(${PROJECT_NAME} main.c ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FLEX_LIBRARIES})

endif()