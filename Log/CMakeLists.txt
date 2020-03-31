cmake_minimum_required(VERSION 3.10)

project(Test)

add_executable(Test tests/main.cpp)

add_subdirectory(LogLib)

target_link_libraries(Test PUBLIC BaseLogger)
target_link_libraries(Test PUBLIC FileLogger)
target_link_libraries(Test PUBLIC StderrLogger)
target_link_libraries(Test PUBLIC StdoutLogger)

target_include_directories(Test PUBLIC
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/LogLib
    ${PROJECT_SOURCE_DIR}/LogLib/include)