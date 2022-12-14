cmake_minimum_required(VERSION 3.22)
project(cplus)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(etl)

link_libraries(etl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(results results.cpp)

add_executable(traits traits.cpp)
target_compile_features(traits PRIVATE cxx_std_14)