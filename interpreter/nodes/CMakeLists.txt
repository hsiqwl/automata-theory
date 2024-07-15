cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(node_traits INTERFACE)
target_include_directories(node_traits INTERFACE include)

add_library(nodes STATIC src/binary_op.cpp src/unary_op.cpp src/identifier_node.cpp src/numeric_literal.cpp src/node.cpp)
target_include_directories(nodes PUBLIC include)
target_link_libraries(nodes visitor)