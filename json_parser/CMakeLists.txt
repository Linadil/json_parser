cmake_minimum_required(VERSION 3.5)

project(json_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#target_include_directories(json_parser PRIVATE include)

set(SOURCES
    src/main.cpp
    src/jsonparser.cpp
    include/jsonparser.h
    include/symbols.h)

add_executable(json_parser ${SOURCES})
