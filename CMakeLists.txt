cmake_minimum_required(VERSION 3.22)
project(cplus)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(etl)

link_libraries(etl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(procedural_programming procedural_programming.cpp)
