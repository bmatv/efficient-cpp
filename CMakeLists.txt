cmake_minimum_required(VERSION 3.16)
project(efficient_cpp)

set(CMAKE_CXX_STANDARD 20)

#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release)
#endif()



set(CMAKE_CXX_FLAGS "-g -O3 -march=native -Wall -pedantic -pthread -mavx2 -m64") # ivybridge -ffast-math

#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -Wall -pedantic")

add_executable(efficient_programs compare.C example.C)

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
add_executable(rational rational.cpp)
add_executable(flying_bird flying_bird.cpp)

add_executable(dynamic_cast 02_dynamic_cast.C)
target_link_libraries(dynamic_cast benchmark::benchmark)

add_executable(ndim_vector_demonstrator ndim_vector.C)

add_library(libbitcount libbitcount.C
        libbitcount.h)
add_executable(bitcount bitcount.C libbitcount.C
        libbitcount.h)

add_executable(bitcount_BM bitcount_BM.cpp libbitcount.C)
target_link_libraries(bitcount_BM benchmark::benchmark)
add_executable(reinterp reinterp.cpp)
add_executable(bitcount_avx bitcount_avx.cpp)

add_executable(fast_pythagorean fast_pythagorean.C)
target_link_libraries(fast_pythagorean benchmark::benchmark)

add_executable(BM_sqrt_pow BM_sqrt_pow.C)
target_link_libraries(BM_sqrt_pow benchmark::benchmark)

add_executable(pythagorean_avx fast_pythagorean_avx.C)
target_link_libraries(pythagorean_avx benchmark::benchmark)
