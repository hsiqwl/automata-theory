cmake_minimum_required(VERSION 3.26)
project(regex_scanner)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(regex_scanner STATIC src/regex_scanner.cpp ../string_utilities/string_utilities.cpp)
target_include_directories(regex_scanner PUBLIC include ../string_utilities)
target_link_libraries(regex_scanner recognizer)
