cmake_minimum_required(VERSION 3.27)
project(regex)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(regex_evaluater)
add_subdirectory(ast)
add_subdirectory(ast_builder)
add_subdirectory(state)
add_subdirectory(dfa)
add_subdirectory(dfa_builder)
add_subdirectory(dfa_operations)
add_subdirectory(regex_engine)

add_executable(main main.cpp)
add_compile_options(-g -fsanitize=address)
add_link_options(-fsanitize=address)
target_link_libraries(main regex_engine)