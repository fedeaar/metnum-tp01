cmake_minimum_required(VERSION 3.21)
project(implementacion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++14 -ggdb3 -g")

add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

set(SOURCE_FILES main.cpp
                 src/EG.h
                 src/Matriz.h
                 src/PageRank.h
                 src/IO.h)

add_executable(TESTS tests/tests.cpp ${SOURCE_FILES})

target_link_libraries(TESTS gtest gtest_main)

add_custom_target(TESTS_valgrind
        valgrind --leak-check=full -v TESTS)