cmake_minimum_required(VERSION 3.27)
project(dfa_builder)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-g)

add_library(dfa_builder STATIC src/dfa_builder.cpp)
target_include_directories(dfa_builder PUBLIC include)
target_link_libraries(dfa_builder regex_tokenizer)
