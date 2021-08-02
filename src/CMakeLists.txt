cmake_minimum_required (VERSION 3.16)

target_sources(mpp_profiler
PRIVATE
# Sources
    main.cpp
# Headers
)

target_include_directories(mpp_profiler PRIVATE ${CMAKE_CURRENT_LIST_DIR})