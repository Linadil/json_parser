cmake_minimum_required(VERSION 3.10)
project(json_parser)

set(CMAKE_CXX_STANDARD 20)


if (TESTS)
    add_subdirectory(test)
endif()
