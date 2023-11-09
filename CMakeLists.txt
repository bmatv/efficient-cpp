cmake_minimum_required(VERSION 3.16)
project(efficient_cpp)
#set(CMAKE_DEPENDS_USE_COMPILER TRUE)
set(CMAKE_CXX_STANDARD 17)

#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release)
#endif()



set(CMAKE_CXX_FLAGS "-g -O3 -mavx2 -Wall -pedantic") # -O3 14576ms,
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -Wall -pedantic")
#message("CMAKE_BUILD_TYPE: " CMAKE_CXX_FLAGS_RELEASE)

add_executable(efficient_programs compare.C example.C) # Sort time: 14033ms (25889223 comparisons)
#add_executable(efficient_programs example.C compare.C) # Sort time: 14033ms (25889223 comparisons)

# with 00_substring_sort_prep in here, multiple issues arise, specifically ` ‘blah’ does not name a type

