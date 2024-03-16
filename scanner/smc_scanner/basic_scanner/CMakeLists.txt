cmake_minimum_required(VERSION 3.26)
project(basic_scanner)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(basic_scanner INTERFACE basic_scanner.h)