# CMakeLists手册
## 目的
* 记录在各种场景下我能用到的`CMakeList.txt`的技巧

## 不言自明
```cmake
cmake_minimum_required(VERSION 3.15)
project(demo VERSION 1.0.0 DESCRIPTION "This is a demo project")

# set(CMAKE_CXX_STANDARD 17) # 默认是14
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.runtime)
# set(ENV{PATH} "$ENV{PATH}:/home/user/xxx")

# if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
# elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
# else()
# message(FATAL_ERROR "Unsupported system")
# endif()

# if (EXISTS ${CMAKE_SOURCE_DIR}/Tranport)
#     add_subdirectory(Tranport)
# else()
#     include(Transport.cmake)
# endif()

# list(APPEND CMAKE_MODULE_PATH /home/user/xxx)
# list(APPEND CMAKE_PREFIX_PATH /home/user/xxx)

find_package(Qt5 REQUIRED COMPONENTS Core Sql Network PATH "/home/user/xxx/Qt/5.15.2/gcc_64" NO_DEFAULT_PATH)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

find_library(ZLIB_LIBRARY zlib PATHS "/usr/local/lib" REQUIRED NO_DEFAULT_PATH)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
find_program(windeployqt windeployqt.exe PATHS ${Qt5_DIR}/../../../bin REQUIRED)
endif()

file(GLOB ${PROJECT_NAME}_SOURCES src/*.cpp inc/*.h) # GLOB_RECURSE 递归
file(REAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/inc ${PROJECT_NAME}_INC_PATH)

add_executable(${PROJECT_NAME})
add_library(${PROJECT_NAME} SHARED) # STATIC|INTERFACE
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core ${ZLIB_LIBRARY}) # PRIVATE|INTERFACE
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INC_PATH})
target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_NAME}.dll .
    COMMAND ${windeployqt} --no-translations $<TARGET_FILE:${PROJECT_NAME}>
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
add_custom_target()
```
## 有用的变量
*   `${CMAKE_BUILD_TYPE}` 构建类型: `Debug`, `Release`
*   `${CMAKE_SYSTEM}` 系统类型
*   `${CMAKE_SYSTEM_NAME}` 系统名称: `Windows`, `Linux`
*   `${CMAKE_C_COMPILER_ID} ${CMAKE_CXX_COMPILER_ID}` 编译器类型: `GNU`, `MSVC`
*   `${CMAKE_C_COMPILER} ${CMAKE_CXX_COMPILER}` 编译器路径
*   `${CMAKE_INSTALL_PREFIX}` 安装路径
*   `${CMAKE_SIZEOF_VOID_P}` 指针大小
## 命令行
*   `--system-information` 输出系统信息
    *   `cmake -G "MinGW Makefiles" --system-information "MinGW System Information.txt"`
    *   `cmake -G "Visual Studio 17 2022" --system-information "VS 17 2022 System Information.txt"`
*   `-S{PATH}` 源路径
*   `-B{PATH}` 构建路径
*   `-G{GENERATOR}` 指定生成器
    *   `-G "Visual Studio 17 2022"`
    *   `-G "MinGW Makefiles"`
*   `-DCMAKE_BUILD_TYPE={Debug|Release}` 指定构建类型
*   `--graphviz={FILE} {path}` 生成依赖图
    *   `CMakeGraphVizOptions.cmake`
        ```cmake
        # 过滤以开头或以结尾的目标
        set(GRAPHVIZ_IGNORE_TARGETS "(^((absl::)|(D:/))|((_dem))$)")
        # 少生成点文件 foo.dot.<target>.dependers
        set(GRAPHVIZ_GENERATE_DEPENDERS FALSE)
        # 少生成点文件 foo.dot.<target>
        set(GRAPHVIZ_GENERATE_PER_TARGET FALSE)
        ```
    *   `dot -Tpng foo.dot -o foo.png` 生成图片
    *   `dot -Tpdf foo.dot -o foo.pdf` 生成PDF

## 故事
### 就是故事
#### 你想find点啥？
都在这个[CMAKE_PREFIX_PATH](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)变量里find。
#### `Doxygen`生成文档
```cmake
find_package(Doxygen)
if(${DOXYGEN_FOUND})
    message(STATUS "Doxygen版本     : ${DOXYGEN_VERSION}")
    set(DOXYGEN_OUTPUT_LANGUAGE "Chinese")
    set(DOXYGEN_EXAMPLE_PATH ${CMAKE_SOURCE_DIR})
    set(DOXYGEN_SOURCE_BROWSER YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_HAVE_DOT NO)
    # set(DOXYGEN_RECURSIVE NO) # 是否递归? 默认YES
    set(DOXYGEN_EXCLUDE_PATTERNS */.git/* */.svn/* */.hg/* */CMakeFiles/* */_CPack_Packages/* DartConfiguration.tcl CMakeCache.txt */.build/* */.runtime/* */ui_*.h */moc_*.h */moc_*.cpp */moc_*.cpp.d */mocs_*.cpp */qrc_*.cpp CommonPlatform DDS ICD include lib LogViewer) # 排除列表来自官方文档, 我把CMakeLists.txt删掉了, 嘻嘻.
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Doxygen) # 官方默认${CMAKE_CURRENT_BINARY_DIR}
    doxygen_add_docs(gen_doc ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/CMakeLists.txt ${CMAKE_SOURCE_DIR}/project.pro)
endif()
```
#### 生成依赖图
```cmake
add_custom_target(graphviz
    COMMAND ${CMAKE_COMMAND} "--graphviz=${CMAKE_PROJECT_NAME}.dot" .
    COMMAND dot -Tpng ${CMAKE_PROJECT_NAME}.dot -o ${I_Transport_PATH}/document/${CMAKE_PROJECT_NAME}.png
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
```
### 算是坑吧
#### vscode远程连接环境变量不生效
我试图在环境变量里添加`J_PC_NAME`环境变量（在`~/.bashrc`文件末尾追加`export J_PC_NAME=xxx`）
用以在CMake项目中区分不同的计算机（环境）
但是我发现重启vscode后，cmake读不到变更。查了一下，是跑在linux上`vscode-server`程序未重启导致的。