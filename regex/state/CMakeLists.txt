cmake_minimum_required(VERSION 3.27)
project(state)

set(CMAKE_CXX_STANDARD 23)

add_library(state STATIC src/state.cpp)
target_include_directories(state PUBLIC include)
target_link_libraries(state transition)