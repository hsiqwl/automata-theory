cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(symbols STATIC src/symbol.cpp src/function.cpp src/var.cpp)
target_include_directories(symbols PUBLIC include)
target_link_libraries(symbols type)