cmake_minimum_required(VERSION 3.16)
project(implementacion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++14 -ggdb3 -g")

add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

set(SOURCE_FILES    src/Matriz.h
                    src/impl/Matriz.hpp
                    src/impl/Matriz-iteradores.hpp
                    src/impl/Matriz-gauss.hpp
                    src/PageRank.h
                    src/IO.h
                    src/MatrizCSR.h
                    src/impl/MatrizCSR.hpp)

add_executable(TESTS-matriz ${SOURCE_FILES} tests/Matriz-test.cpp)
# add_custom_target(TESTS_valgrind valgrind --leak-check=full -v TESTS)
# add_executable(PageRank ${SOURCE_FILES})
# add_executable(main ${SOURCE_FILES})

target_link_libraries(TESTS-matriz gtest gtest_main)
