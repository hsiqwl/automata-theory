cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(call_stack STATIC src/call_stack.cpp)
target_include_directories(call_stack PUBLIC include)
target_link_libraries(call_stack activation_record)