cmake_minimum_required(VERSION 3.26)
project(pattern_scanner)


set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(smc_scanner STATIC
        src/pattern_scanner.cpp
        src/pattern_scanner_sm.cpp
        ../../string_utilities/string_utilities.h
        ../../string_utilities/string_utilities.cpp)
target_include_directories(smc_scanner PUBLIC include)
target_link_libraries(smc_scanner join_scanner create_scanner id_scanner info_collector)
