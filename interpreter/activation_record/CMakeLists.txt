cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(activation_record STATIC src/activation_record.cpp)
target_include_directories(activation_record PUBLIC include)
target_link_libraries(activation_record values)