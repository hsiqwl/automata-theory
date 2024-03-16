cmake_minimum_required(VERSION 3.26)
project(recognizer)

set(CMAKE_CXX_STANDARD 20)
add_library(recognizer INTERFACE)
target_include_directories(recognizer INTERFACE include)