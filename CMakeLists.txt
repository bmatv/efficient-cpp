cmake_minimum_required(VERSION 3.16)
project(efficient_cpp)

set(CMAKE_CXX_STANDARD 20)

#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release)
#endif()



set(CMAKE_CXX_FLAGS "-g -O3 -Wall -pedantic -pthread") # -O3 -mavx2
# TODO CMake should check if AVX2 is available and enable the flag automatically

#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -Wall -pedantic")

add_executable(efficient_programs compare.C example.C
        ndim_vector.C)

add_executable(clocks clocks.cpp)

add_executable(threading threading.cpp)

add_executable(superscalar 01_superscalar.C)

add_executable(branches branches.cpp)

add_executable(clamp_test branch_clamp.cpp)

find_package(benchmark REQUIRED)

target_link_libraries(superscalar benchmark::benchmark)

target_link_libraries(branches benchmark::benchmark)

target_link_libraries(clamp_test benchmark::benchmark)
add_executable(avx_test avx_test.cpp)
add_executable(find_sum_elements find_sum_elements.cpp)

add_library(libbitcount libbitcount.C
        libbitcount.h)

add_executable(bitcount bitcount.C libbitcount.C
        libbitcount.h)

add_executable(rational rational.cpp)
add_executable(ndim_vector_demonstrator ndim_vector.C)

add_executable(bitcount_BM bitcount_BM.cpp libbitcount.C)
target_link_libraries(bitcount_BM benchmark::benchmark)
