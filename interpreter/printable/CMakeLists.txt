cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(printable INTERFACE)
target_include_directories(printable INTERFACE include)