cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(type STATIC src/type_holder.cpp)
target_include_directories(type PUBLIC include)


add_library(values STATIC src/signed_value.cpp src/unsigned_value.cpp src/cell_value.cpp)
target_include_directories(values PUBLIC include)
target_link_libraries(values type cell)
