cmake_minimum_required(VERSION 3.27)
project(regex_tokenizer)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)

add_library(regex_tokenizer STATIC src/regex_tokenizer.cpp src/token.cpp src/regex_operator.cpp)
target_include_directories(regex_tokenizer PUBLIC include)