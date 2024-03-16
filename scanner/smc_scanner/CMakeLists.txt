cmake_minimum_required(VERSION 3.26)
project(smc_scanner)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(basic_scanner)
add_subdirectory(create_scanner)
add_subdirectory(join_scanner)
add_subdirectory(id_scanner)
add_subdirectory(pattern_scanner)