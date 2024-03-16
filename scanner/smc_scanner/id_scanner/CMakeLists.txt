cmake_minimum_required(VERSION 3.26)
project(id_scanner)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(id_scanner STATIC src/id_scanner.cpp src/id_scanner_sm.cpp)
target_include_directories(id_scanner PUBLIC include)
target_link_libraries(id_scanner basic_scanner)
