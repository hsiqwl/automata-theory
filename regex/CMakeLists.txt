cmake_minimum_required(VERSION 3.27)
project(regex)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(regex_evaluater)
add_subdirectory(dfa_builder)
add_executable(main main.cpp)
target_link_libraries(main regex_tokenizer dfa_builder)