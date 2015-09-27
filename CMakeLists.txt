cmake_minimum_required(VERSION 3.2)
project(LZW_Archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LZW_Archiver_SOURCE_DIR})
add_executable(LZW_Archiver ${SOURCE_FILES} core.h core.cpp )

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
add_executable(unittest unittest.cpp core.h core.cpp)

target_link_libraries(unittest
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )

add_test(unittest unittest)



