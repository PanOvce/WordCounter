cmake_minimum_required(VERSION 3.6)
project(WordCounter)

SET(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-std=c++14 -O3 -pthread ")
find_package (Threads)

set(SOURCE_FILES
        main.cpp
        sequence.hpp
        sequence.cpp parallel.hpp counter.hpp counter.cpp parallel.cpp)
add_executable(WordCounter ${SOURCE_FILES})