cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(value_interface INTERFACE)
target_include_directories(value_interface INTERFACE include)

add_library(value_interface_implementation STATIC src/value_matrix.cpp src/value_signed.cpp src/value_unsigned.cpp src/value_cell.cpp)
target_include_directories(value_interface_implementation PUBLIC include)
target_link_libraries(value_interface_implementation INTERFACE value_interface)
target_link_libraries(value_interface_implementation PUBLIC cell)