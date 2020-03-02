cmake_minimum_required(VERSION 3.15)
project(rosalind)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DNAME=ba3m)
add_executable(SOLUTION main.cpp solver.cpp rosalind.cpp)