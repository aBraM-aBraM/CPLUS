cmake_minimum_required(VERSION 3.22)
project(cplus)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(etl)

link_libraries(etl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(results examples/results.cpp)

add_executable(traits examples/traits.cpp)
target_compile_features(traits PRIVATE cxx_std_14)

add_executable(mocks examples/mocks.cpp)
