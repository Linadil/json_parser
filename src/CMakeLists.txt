cmake_minimum_required(VERSION 3.10)
project(json_parser)

set(CMAKE_CXX_STANDARD 20)

set(LIB_NAME json_parser)
set(SOURCES
    jsonparser.cpp
    jsontree.cpp
)


add_library(${LIB_NAME} STATIC ${SOURCES})
