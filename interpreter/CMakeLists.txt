cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(cell)
add_subdirectory(symbol)
add_subdirectory(symbol_table)
add_subdirectory(object_factory)
add_subdirectory(value)

add_library(parsing_driver STATIC parsing_driver/grammar.tab.cc parsing_driver/parsing_driver.cpp parsing_driver/lex.yy.cc)
target_include_directories(parsing_driver PUBLIC parsing_driver/symbol_table/include)
add_executable(interpreter main.cpp)
target_link_libraries(interpreter parsing_driver value_interface_implementation)
