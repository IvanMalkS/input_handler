cmake_minimum_required(VERSION 3.29)
project(input_handler)

set(CMAKE_CXX_STANDARD 20)

add_executable(input_handler main.cpp
        handlers/input/input_handler.cpp
        handlers/input/input_handler.h
)

configure_file(
        "${CMAKE_SOURCE_DIR}/config.json"
        "${CMAKE_BINARY_DIR}/config.json"
        COPYONLY
)