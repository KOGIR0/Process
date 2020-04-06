cmake_minimum_required(VERSION 3.10)

add_library(LogLib "./src/BaseLogger.cpp" 
                    "./src/FileLogger.cpp" 
                    "./src/StderrLogger.cpp" 
                    "./src/StdoutLogger.cpp")

target_include_directories(LogLib PUBLIC ./include)