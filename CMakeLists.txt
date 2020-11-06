cmake_minimum_required(VERSION 3.1)

project(
    rc
)

# use fPIC for all libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(minimal-latency-streaming-protocol)

# this is our main target
add_library(rc SHARED robot_control.c)
target_include_directories(rc PRIVATE minimal-latency-streaming-protocol)

target_link_libraries(rc mlsp)
