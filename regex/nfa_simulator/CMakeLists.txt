cmake_minimum_required(VERSION 3.27)
project(nfa_simulator)

set(CMAKE_CXX_STANDARD 23)

add_library(nfa_simulator STATIC src/nfa_simulator.cpp)
target_include_directories(nfa_simulator PUBLIC include)