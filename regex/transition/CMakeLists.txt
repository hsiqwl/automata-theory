cmake_minimum_required(VERSION 3.27)
project(transition)

set(CMAKE_CXX_STANDARD 23)

add_library(transition STATIC src/transition.cpp)
target_include_directories(transition PUBLIC include ../state/include)
target_link_libraries(transition matcher single_character_matcher character_class_matcher)