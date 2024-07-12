cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(ast_printer STATIC src/ast_printer.cpp)
target_include_directories(ast_printer PUBLIC include)
target_link_libraries(ast_printer ast)