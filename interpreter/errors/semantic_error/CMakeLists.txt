cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(semantic_errors STATIC src/semantic_error.cpp)
target_include_directories(semantic_errors PUBLIC include)
target_link_libraries(semantic_errors locations type)