cmake_minimum_required(VERSION 3.16)
project(pagerank)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++14 -ggdb3 -g")

add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

set(SOURCE_FILES
        src/matriz.h
        src/matriz/matriz_base.h
        src/matriz/matriz_alt.h
        src/impl/matriz.hpp
        src/impl/matriz/matriz_base.cpp
        src/impl/matriz/matriz_alt.cpp
        src/pagerank.h
        src/impl/pagerank.hpp
        src/IO.h
        src/impl/IO.cpp
        src/impl/IO.hpp)
        

add_executable(TESTS-matriz-base ${SOURCE_FILES} tests/matriz-tests.cpp)
target_compile_definitions(TESTS-matriz-base PUBLIC ESTR=1)
target_link_libraries(TESTS-matriz-base gtest gtest_main)

add_executable(TESTS-matriz-alt  ${SOURCE_FILES} tests/matriz-tests.cpp)
target_compile_definitions(TESTS-matriz-alt PUBLIC ESTR=2)
target_link_libraries(TESTS-matriz-alt gtest gtest_main)

add_executable(TESTS-pagerank-base ${SOURCE_FILES} tests/pagerank-tests.cpp)
target_compile_definitions(TESTS-pagerank-base PUBLIC ESTR=1)
target_link_libraries(TESTS-pagerank-base gtest gtest_main)

add_executable(TESTS-pagerank-alt ${SOURCE_FILES} tests/pagerank-tests.cpp)
target_compile_definitions(TESTS-pagerank-alt PUBLIC ESTR=2)
target_link_libraries(TESTS-pagerank-alt gtest gtest_main)

add_executable(tp1 ${SOURCE_FILES} main.cpp)
target_compile_definitions(tp1 PUBLIC ESTR=2)
