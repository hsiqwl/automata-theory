cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(symbol_table STATIC src/scoped_symbol_table.cpp)
target_include_directories(symbol_table PUBLIC include)
target_link_libraries(symbol_table symbols)