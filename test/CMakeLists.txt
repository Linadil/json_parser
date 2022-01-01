cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 20)

set(EXEC test)
set(LIB_TO_TEST ${CMAKE_SOURCE_DIR}/build/libjson_parser.a)
set(SOURCES
    test.cpp
)


enable_testing()
find_package(gtest)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${EXEC} ${SOURCES})

target_link_libraries(${EXEC} ${GTEST_LIBRARIES} pthread)
target_link_libraries(${EXEC} ${LIB_TO_TEST})
