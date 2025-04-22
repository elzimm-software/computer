cmake_minimum_required(VERSION 3.29)
project(igor_computer)

set(CMAKE_CXX_STANDARD 20)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/add.sml ${CMAKE_CURRENT_BINARY_DIR}/add.sml COPYONLY)

add_executable(igor_computer main.cpp Computer.h)
add_executable(strtosml strtosml.cpp)
