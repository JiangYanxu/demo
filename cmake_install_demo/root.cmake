# Include once.
if(NOT ROOT_CMAKE_CONFIG_FILE_INCLUDED)
set(ROOT_CMAKE_CONFIG_FILE_INCLUDED TRUE)

set(MY_TEMPORARY_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/0temp CACHE STRING "Temporary directory for build")
set(MY_OUTPUT_DIRECTORY ${MY_TEMPORARY_DIRECTORY}/build CACHE STRING "Output directory for build")

# Global variables
file(REAL_PATH ${CMAKE_CURRENT_LIST_DIR} MY_ROOT)

# C/C++ standard
set(CMAKE_CXX_STANDARD 17) # default mingw:17 msvc:14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17) # default mingw:17 msvc:99
set(CMAKE_C_STANDARD_REQUIRED ON)

# OUTPUT DIRECTORY
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY}/archive)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY}/pdb)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY}/runtime)
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY}/compile)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY}/library)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build Type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
    message(STATUS "CMAKE_BUILD_TYPE not set, default to Debug")
endif()

# if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#     set(CMAKE_SHARED_LIBRARY_PREFIX "") # default is "lib"
#     list(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".dll") # default is ".dll.a;.a;.lib"
# endif()

include(GNUInstallDirs)
set(CMAKE_INSTALL_PREFIX ${MY_TEMPORARY_DIRECTORY}/install CACHE STRING "Install directory" FORCE)

endif() # ROOT_CMAKE_CONFIG_FILE_INCLUDED

# cmake -G "MinGW Makefiles" --system-information "MinGW System Information.txt" && cmake -G "Visual Studio 17 2022" --system-information "VS 17 2022 System Information.txt"