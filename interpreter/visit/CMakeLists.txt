cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(visit_func INTERFACE)
target_include_directories(visit_func INTERFACE include)

target_link_libraries(visit_func INTERFACE node_traits)