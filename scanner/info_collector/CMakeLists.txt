cmake_minimum_required(VERSION 3.26)
project(info_collector)

set(CMAKE_CXX_STANDARD 20)
add_library(info_collector STATIC src/info_collector.cpp ../string_utilities/string_utilities.h ../string_utilities/string_utilities.cpp)
target_include_directories(info_collector PUBLIC include)