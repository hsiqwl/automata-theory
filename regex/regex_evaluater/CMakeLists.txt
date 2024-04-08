cmake_minimum_required(VERSION 3.27)
project(regex_tokenizer)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-g)

add_library(token STATIC src/token.cpp
        src/operator_token.cpp
        src/repetition_operator.cpp
        src/single_character.cpp
        src/character_class.cpp)
target_include_directories(token PUBLIC include)

add_library(regex_tokenizer STATIC src/regex_tokenizer.cpp)
target_include_directories(regex_tokenizer PUBLIC include)
target_link_libraries(regex_tokenizer token)