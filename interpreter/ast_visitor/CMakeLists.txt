cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(visitor INTERFACE)
target_include_directories(visitor INTERFACE include)

add_library(printer STATIC src/printer.cpp)
target_include_directories(printer PUBLIC include)
target_link_libraries(printer visitor node_traits)