cmake_minimum_required(VERSION 3.16)
project(efficient_cpp)

#set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


#set(CMAKE_CXX_FLAGS "-O3 -mavx2 -Wall -pedantic") # -O3 14576ms,
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -Wall -pedantic")
message("CMAKE_BUILD_TYPE: " CMAKE_CXX_STANDARD)

add_executable(efficient_programs example.C # with 00_substring_sort_prep in here, multiple issues arise, specifically ` ‘blah’ does not name a type
        compare.C)

