cmake_minimum_required(VERSION 3.16)
project(implementacion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++14 -ggdb3 -g")

add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

set(SOURCE_FILES
        src/matriz.h
        src/impl/matriz/matriz.hpp
        src/matriz_base.h
        src/impl/matriz/matriz_base.cpp
        src/matriz_alt.h
        src/impl/matriz/matriz_alt.cpp
        src/pagerank.h
        src/impl/pagerank.cpp
        src/IO.h
        src/impl/IO.cpp
)

add_executable(TESTS-matriz-base ${SOURCE_FILES} tests/matriz-tests.cpp)
target_compile_definitions(TESTS-matriz-base PUBLIC ESTR=1)
target_link_libraries(TESTS-matriz-base gtest gtest_main)

add_executable(TESTS-matriz-alt  ${SOURCE_FILES} tests/matriz-tests.cpp)
target_compile_definitions(TESTS-matriz-alt PUBLIC ESTR=2)
target_link_libraries(TESTS-matriz-alt  gtest gtest_main)

add_executable(TESTS-pagerank ${SOURCE_FILES} tests/pagerank-tests.cpp)
target_link_libraries(TESTS-pagerank    gtest gtest_main)

add_executable(main ${SOURCE_FILES} main.cpp)

# add_custom_target(TESTS_valgrind valgrind --leak-check=full -v TESTS)
