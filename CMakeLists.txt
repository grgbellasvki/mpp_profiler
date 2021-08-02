cmake_minimum_required (VERSION 3.16)
project (mpp_profiler CXX)

# Default Version of C++
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Version Number
set (mpp_profiler_VERSION_MAJOR 0)
set (mpp_profiler_VERSION_MINOR 1)

# Project Directories
set (mpp_profiler_SRC_DIR ${mpp_profiler_SOURCE_DIR}/src)
set (mpp_profiler_EXE_DIR ${mpp_profiler_SOURCE_DIR}/exe)

# Install Directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${mpp_profiler_SOURCE_DIR}/install
        CACHE PATH "Setting up the installation directory" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Eigen Directory
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# Compiling and Linking
add_executable(mpp_profiler "")

# Adding subdirectory
add_subdirectory(${mpp_profiler_SRC_DIR})

# Arguably a bad option! Feel free to change.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Default build type: Release" FORCE)
endif()

# Linking libraries
target_link_libraries(mpp_profiler PRIVATE Eigen3::Eigen)

find_package(mutation++ REQUIRED)
target_link_libraries(mpp_profiler
PRIVATE
    mutation++::mutation++
)

# Adding compilation options
target_compile_options(mpp_profiler PRIVATE -Wall -Wextra -pedantic) # -Werror)

# Installing
install (TARGETS mpp_profiler DESTINATION ${mpp_profiler_EXE_DIR})
