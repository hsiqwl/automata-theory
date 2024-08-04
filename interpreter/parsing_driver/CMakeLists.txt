cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(locations INTERFACE)
target_include_directories(locations INTERFACE include)

add_library(parse_driver STATIC src/grammar.tab.cc src/lex.yy.cc src/parsing_driver.cpp)
target_include_directories(parse_driver PUBLIC include)
target_link_libraries(parse_driver ast)
