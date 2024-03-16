cmake_minimum_required(VERSION 3.26)
project(create_scanner)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(create_scanner STATIC src/create_scanner.cpp src/create_scanner_sm.cpp)
target_include_directories(create_scanner PUBLIC include)
target_link_libraries(create_scanner basic_scanner)
