cmake_minimum_required(VERSION 3.27)
project(utilities)

set(CMAKE_CXX_STANDARD 23)

add_library(token_info src/terminal_info.cpp src/repetition_info.cpp)
target_include_directories(token_info PUBLIC include)