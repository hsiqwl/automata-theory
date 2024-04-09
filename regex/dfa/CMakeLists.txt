cmake_minimum_required(VERSION 3.27)
project(dfa)

set(CMAKE_CXX_STANDARD 23)

add_library(dfa STATIC src/dfa.cpp)
target_include_directories(dfa PUBLIC include)
target_link_libraries(dfa state transition matcher)

add_library(character_dfa STATIC src/character_dfa.cpp)
target_include_directories(character_dfa PUBLIC include)
target_link_libraries(character_dfa dfa)
