cmake_minimum_required(VERSION 3.16)
project(implementacion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++14 -ggdb3 -g")

add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

set(SOURCE_FILES
        src/matriz-repr.h
        src/impl/matriz/matriz-repr-base.hpp
        src/impl/matriz/matriz-repr-alt.hpp
        src/matriz.h
        src/impl/matriz/matriz.hpp
        src/impl/matriz/matriz-interfaz.hpp
        src/impl/matriz/matriz-iteradores.hpp
        src/impl/matriz/matriz-operadores.hpp
        src/impl/matriz/matriz-gauss.hpp
        src/pagerank.h
        src/impl/pagerank.cpp
        src/IO.h
        src/impl/IO.cpp)

add_executable(TESTS-matriz ${SOURCE_FILES} tests/Matriz-tests.cpp)
add_executable(TESTS-pagerank ${SOURCE_FILES} tests/Pagerank-tests.cpp)
add_executable(TESTS-matrizalt ${SOURCE_FILES} tests/MatrizAlt-tests.cpp)
# add_custom_target(TESTS_valgrind valgrind --leak-check=full -v TESTS)
# add_executable(pagerank ${SOURCE_FILES})
add_executable(main ${SOURCE_FILES} main.cpp)

target_link_libraries(TESTS-matriz gtest gtest_main)
target_link_libraries(TESTS-pagerank gtest gtest_main)
target_link_libraries(TESTS-matrizalt gtest gtest_main)
