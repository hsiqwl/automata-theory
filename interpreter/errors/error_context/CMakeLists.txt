cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(error_context STATIC src/semantic_error_context.cpp)
target_include_directories(error_context PUBLIC include)
target_link_libraries(error_context semantic_errors printable)