cmake_minimum_required(VERSION 3.16)
project(efficient_cpp)

set(CMAKE_CXX_STANDARD 20)

#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release)
#endif()

find_package(benchmark REQUIRED)
# set(CMAKE_CXX_FLAGS "-g -O3 -march=native -Wall -pedantic -pthread -std=c++20") # ivybridge -ffast-math
set(CMAKE_CXX_FLAGS "-g -O3 -pedantic")

#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pedantic")

add_executable(efficient_programs compare.C example.C)

add_executable(clocks clocks.cpp)

add_executable(threading threading.cpp)
target_compile_options(threading PRIVATE -Wall -Wextra -pthread -O3)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # will match both Clang and AppleClang
    target_compile_options(threading PRIVATE -fexperimental-library)
    # -fexperimental-library is needed for clang17 to get access to jthread
endif()

add_executable(superscalar 01_superscalar.C)

add_executable(branches branches.cpp)
message("CHECKING if x86 CPU TARGET")
message("CMAKE_CXX_COMPILER_TARGET IS ${CMAKE_CXX_COMPILER_TARGET}")
message("CMAKE_SYSTEM_PROCESSOR IS ${CMAKE_SYSTEM_PROCESSOR}")
if (CMAKE_CXX_COMPILER_TARGET MATCHES "x86_64" OR CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    message("x86 CPU TARGET FOUND. ENABLING EXTRA EXECUTABLES")
    add_executable(clamp_test branch_clamp.cpp) # use of x86 only header so does not build on ARM, how to turn it off in cmake if ARM detected? Or better yet, howe to build it only for x86 arch
    target_link_libraries(clamp_test benchmark::benchmark)

    add_executable(avx_test avx_test.cpp)
    add_executable(bitcount_avx bitcount_avx.cpp)

    add_executable(pythagorean_avx fast_pythagorean_avx.C)
    target_link_libraries(pythagorean_avx benchmark::benchmark)
    add_library(libbitcount libbitcount.C libbitcount.h)
    add_executable(bitcount bitcount.C libbitcount.C libbitcount.h)

    add_executable(bitcount_BM bitcount_BM.cpp libbitcount.C)
    target_link_libraries(bitcount_BM benchmark::benchmark)
endif()


target_link_libraries(superscalar benchmark::benchmark)

target_link_libraries(branches benchmark::benchmark)

add_executable(find_sum_elements find_sum_elements.cpp)
add_executable(rational rational.cpp)

add_executable(dynamic_cast 02_dynamic_cast.C)
target_link_libraries(dynamic_cast benchmark::benchmark)

add_executable(ndim_vector_demonstrator ndim_vector.C)

add_executable(reinterp reinterp.cpp)

add_executable(fast_pythagorean fast_pythagorean.C)
target_link_libraries(fast_pythagorean benchmark::benchmark)

add_executable(BM_sqrt_pow BM_sqrt_pow.C)
target_link_libraries(BM_sqrt_pow benchmark::benchmark)


add_executable(01_cast design-patterns/01_cast.C)
add_executable(02_dynamic_cast design-patterns/02_dynamic_cast.C)
target_link_libraries(02_dynamic_cast benchmark::benchmark)
add_executable(flying_bird design-patterns/flying_bird.cpp)

add_executable(repeating_series repeating_series.C)

add_executable(struct_init struct_init.C)
