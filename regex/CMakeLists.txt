cmake_minimum_required(VERSION 3.27)
project(regex)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(regex_evaluater)
add_subdirectory(dfa_builder)
add_subdirectory(matcher)
add_subdirectory(state)
add_subdirectory(transition)
add_subdirectory(dfa)
add_executable(main main.cpp)
target_link_libraries(main regex_tokenizer dfa_builder)