cmake_minimum_required(VERSION 3.10)
project(rosalind)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DNAME=ba3c)

add_library(rosalind solver/rosalind.cpp)
add_library(solver
        solver/abstract_solver.cpp
        solver/assembly_solver.cpp
        solver/common_solver.cpp
        solver/recombination_solver.cpp
        solver/trees_solver.cpp)

add_executable(run main.cpp)

target_link_libraries(solver PRIVATE rosalind)
target_link_libraries(run PRIVATE solver)