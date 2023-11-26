cmake_minimum_required(VERSION 3.16)
project(efficient_cpp)

set(CMAKE_CXX_STANDARD 20)

#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release)
#endif()



set(CMAKE_CXX_FLAGS "-g -O3 -mavx2 -Wall -pedantic -pthread")

#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -Wall -pedantic")

add_executable(efficient_programs compare.C example.C)

add_executable(clocks clocks.cpp)

add_executable(threading threading.cpp)

add_executable(superscalar 01_superscalar.C)

find_package(benchmark REQUIRED)

target_link_libraries(superscalar benchmark::benchmark)