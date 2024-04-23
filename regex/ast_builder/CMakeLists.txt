cmake_minimum_required(VERSION 3.27)
project(ast_builder)

set(CMAKE_CXX_STANDARD 23)

add_library(ast_builder STATIC src/ast_builder.cpp)
target_include_directories(ast_builder PUBLIC include)
target_link_libraries(ast_builder ast regex_tokenizer)