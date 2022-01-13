cmake_minimum_required(VERSION 3.10)
project(json_parser)

add_compile_options(-g3 -ggdb)

set(CMAKE_CXX_STANDARD 20)

set(EXEC test)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
    test.cpp
)
set(TEST_SOURCES
    ${SRC_DIR}/jsonitem.cpp
    ${SRC_DIR}/jsonparser.cpp
)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${EXEC} ${SOURCES} ${TEST_SOURCES})

target_link_libraries(${EXEC} ${GTEST_LIBRARIES} pthread)
