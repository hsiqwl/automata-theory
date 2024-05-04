cmake_minimum_required(VERSION 3.27)
project(tests)

set(CMAKE_CXX_STANDARD 23)

add_executable(test tests.cpp)
target_link_libraries(test gtest gmock pthread regex_engine)