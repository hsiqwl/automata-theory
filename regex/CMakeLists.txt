cmake_minimum_required(VERSION 3.27)
project(regex)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(regex_evaluater)
add_subdirectory(ast)
add_subdirectory(ast_builder)

add_executable(main main.cpp)
target_link_libraries(main ast_builder)