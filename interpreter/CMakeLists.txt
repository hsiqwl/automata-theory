cmake_minimum_required(VERSION 3.27)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-g)

add_subdirectory(printable)
add_subdirectory(cell)
add_subdirectory(symbol)
add_subdirectory(symbol_table)
add_subdirectory(object_factory)
add_subdirectory(value)
add_subdirectory(errors)
add_subdirectory(nodes)
add_subdirectory(ast)
add_subdirectory(ast_visitor)
add_subdirectory(parsing_driver)
add_subdirectory(activation_record)
add_subdirectory(call_stack)

add_executable(main main.cpp)
target_link_libraries(main parse_driver printer semantic_analyzer)

