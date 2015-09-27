cmake_minimum_required(VERSION 3.2)
project(LZW_Archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LZW_Archiver_SOURCE_DIR})
add_executable(LZW_Archiver ${SOURCE_FILES} core.h core.cpp)