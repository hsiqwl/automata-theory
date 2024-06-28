cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(cell STATIC src/cell.cpp)
target_include_directories(cell PUBLIC include)
