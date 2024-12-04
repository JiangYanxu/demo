# Include Once
if(NOT QxOrm_ROOT_CMAKE_CONFIG_FILE_INCLUDED)
set(QxOrm_ROOT_CMAKE_CONFIG_FILE_INCLUDED TRUE)

find_package(Qt5 COMPONENTS Core Sql)
if(Qt5_FOUND)
    file(REAL_PATH ${CMAKE_CURRENT_LIST_DIR} QxOrm_HOME)

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            if(CMAKE_BUILD_TYPE STREQUAL "Debug")
                find_library(QxOrm_LIBRARY NAMES QxOrm.lib PATHS ${QxOrm_HOME}/lib NO_DEFAULT_PATH REQUIRED)
            elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
                find_library(QxOrm_LIBRARY NAMES QxOrmd.lib PATHS ${QxOrm_HOME}/lib NO_DEFAULT_PATH REQUIRED)
            else()
                message(FATAL_ERROR "Unsupported CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")
            endif()
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            if(CMAKE_BUILD_TYPE STREQUAL "Debug")
                find_library(QxOrm_LIBRARY NAMES libQxOrmd.a PATHS ${QxOrm_HOME}/lib NO_DEFAULT_PATH REQUIRED)
            elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
                find_library(QxOrm_LIBRARY NAMES libQxOrm.a PATHS ${QxOrm_HOME}/lib NO_DEFAULT_PATH REQUIRED)
            else()
                message(FATAL_ERROR "Unsupported CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")
            endif()
        else()
            message(FATAL_ERROR "Unsupported CMAKE_CXX_COMPILER_ID : ${CMAKE_CXX_COMPILER_ID}")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            find_library(QxOrm_LIBRARY NAMES QxOrmd PATHS ${QxOrm_HOME}/lib_linux NO_DEFAULT_PATH REQUIRED)
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            find_library(QxOrm_LIBRARY NAMES QxOrm PATHS ${QxOrm_HOME}/lib_linux NO_DEFAULT_PATH REQUIRED)
        else()
            message(FATAL_ERROR "Unsupported CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")
        endif()
    else()
        message(FATAL_ERROR "Unsupported CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")
    endif()

    message(STATUS "QxOrm_LIBRARY : ${QxOrm_LIBRARY}")

    add_library(QxOrm INTERFACE)
    target_link_libraries(QxOrm INTERFACE ${QxOrm_LIBRARY})
    target_link_libraries(QxOrm INTERFACE Qt5::Core Qt5::Sql)
    target_include_directories(QxOrm INTERFACE ${QxOrm_HOME}/include)

    # 来自 QxOrm/QxOrm.cmake
    target_compile_definitions(QxOrm INTERFACE $<$<CONFIG:Debug>:_QX_MODE_DEBUG>
                                               $<$<CONFIG:Release>:_QX_MODE_RELEASE>
                                               $<$<CONFIG:RelWithDebInfo>:_QX_MODE_RELEASE>
                                               $<$<CONFIG:MinSizeRel>:_QX_MODE_RELEASE>
                                               $<$<CONFIG:None>:_QX_MODE_RELEASE>
                                               $<$<CONFIG:>:_QX_MODE_RELEASE>)
    target_compile_definitions(QxOrm INTERFACE _QX_STATIC_BUILD _QX_UNITY_BUILD)

    # GCC对链接顺序有要求
    # gcc -o bin -lQxOrm -lQt5::Sql -lQt5::Core 不会报错。
    # gcc -o bin -lQt5::Sql -lQt5::Core -lQxOrm 则会报错。
    # 需要调整target_link_libraries的顺序
    # 但经我测试（win11 cmake version 3.30.2），链接顺序仍然不符合直觉。感觉像是个CMake的Bug。
    message(NOTICE "If QxOrm link is wrong, here are some ideas to fix it:\n"
                   "\tgcc -o bin -lQxOrm -lQt5::Sql -lQt5::Core : is available.\n"
                   "\tgcc -o bin -lQt5::Sql -lQt5::Core -lQxOrm : will fail the link.\n"
                   "\tYou need to adjust the order of cmake links.")
else() # Qt5 not found
    message(WARNING "Qt5 not found, QxOrm will not be available.")
endif() # Qt5_FOUND

endif() # QxOrm_ROOT_CMAKE_CONFIG_FILE_INCLUDED 