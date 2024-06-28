cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(ast STATIC src/operation_node.cpp src/operand_node.cpp)
target_include_directories(ast PUBLIC include)