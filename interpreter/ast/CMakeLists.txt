cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(ast STATIC src/ast.cpp)
target_include_directories(ast PUBLIC include)
target_link_libraries(ast nodes printer interpreter)