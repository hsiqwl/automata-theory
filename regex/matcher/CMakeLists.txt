cmake_minimum_required(VERSION 3.27)
project(matcher)

set(CMAKE_CXX_STANDARD 23)

add_library(matcher INTERFACE include/matcher.h)
add_library(single_character_matcher STATIC src/single_character_matcher.cpp)
add_library(character_class_matcher STATIC src/character_class_matcher.cpp)
add_library(any_matcher STATIC src/any_matcher.cpp)

target_include_directories(single_character_matcher PUBLIC include)
target_link_libraries(single_character_matcher matcher)

target_include_directories(character_class_matcher PUBLIC include)
target_link_libraries(character_class_matcher matcher)

target_include_directories(any_matcher PUBLIC include)
target_link_libraries(any_matcher matcher)