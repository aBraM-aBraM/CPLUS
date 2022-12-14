cmake_minimum_required(VERSION 3.22)
project(cplus)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(etl)

add_executable(cplus main.cpp)
target_link_libraries(cplus PUBLIC etl)
target_include_directories(cplus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_options(cplus PUBLIC "-Wl, -nostdlib")
