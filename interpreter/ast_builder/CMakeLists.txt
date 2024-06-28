cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(ast_builder STATIC src/ast_builder.cpp)
target_include_directories(ast_builder PUBLIC include)
target_link_libraries(ast_builder ast)