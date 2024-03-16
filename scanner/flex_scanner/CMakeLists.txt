cmake_minimum_required(VERSION 3.26)
project(flex_scanner)

set(CMAKE_CXX_STANDARD 20)
add_library(flex_scanner STATIC src/flex_scanner.cpp src/lex.yy.cc)
target_include_directories(flex_scanner PUBLIC include)
target_link_libraries(flex_scanner info_collector recognizer)