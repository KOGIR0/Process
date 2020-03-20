cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

project(Homework1)

include_directories(include)

add_library(Process STATIC lib/Process.cpp)

add_executable(main tests/main.cpp)

target_link_libraries(main Process)

