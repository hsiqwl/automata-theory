cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(node_traits INTERFACE)
target_include_directories(node_traits INTERFACE include)

add_library(ast STATIC src/binary_op.cpp src/unary_op.cpp src/identifier_node.cpp src/numeric_literal.cpp)
target_include_directories(ast PUBLIC include)