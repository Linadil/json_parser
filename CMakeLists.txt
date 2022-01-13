cmake_minimum_required(VERSION 3.10)
project(json_parser)

add_compile_options(-g3 -ggdb)

set(CMAKE_CXX_STANDARD 20)


if (TESTS)
    add_subdirectory(test)
endif()
