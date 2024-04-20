cmake_minimum_required(VERSION 3.27)
project(regex)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(regex_evaluater)
add_subdirectory(state)
add_subdirectory(dfa)
add_subdirectory(dfa_builder)