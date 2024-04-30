cmake_minimum_required(VERSION 3.27)
project(dfa_operations)

set(CMAKE_CXX_STANDARD 23)
add_library(dfa_operations STATIC src/dfa_operations.cpp)
target_include_directories(dfa_operations PUBLIC include)
target_link_libraries(dfa_operations dfa)