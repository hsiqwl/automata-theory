cmake_minimum_required(VERSION 3.26)
project(generator)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(generator STATIC src/generator.cpp)
target_include_directories(generator PUBLIC include)

add_executable(gen src/gen.cpp)
target_link_libraries(gen generator)