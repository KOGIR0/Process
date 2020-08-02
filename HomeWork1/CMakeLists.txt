cmake_minimum_required(VERSION 3.10)

project(Test)

add_executable(Test tests/main.cpp)

add_subdirectory(LogLib)

target_link_libraries(Test LogLib)