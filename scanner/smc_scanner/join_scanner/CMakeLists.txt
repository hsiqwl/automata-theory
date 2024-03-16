cmake_minimum_required(VERSION 3.26)
project(join_scanner)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(join_scanner STATIC src/join_scanner.cpp src/join_scanner_sm.cpp)
target_include_directories(join_scanner PUBLIC include)
target_link_libraries(join_scanner basic_scanner)