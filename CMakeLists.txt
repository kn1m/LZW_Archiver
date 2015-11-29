cmake_minimum_required(VERSION 3.3)
project(LZW_Archiver)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Optimization flags

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -freorder-blocks -ftree-loop-vectorize -ftree-slp-vectorize -falign-functions
# -falign-jumps -falign-loops -fcaller-saves -fcrossjumping -fcse-follow-jumps -fexpensive-optimizations
# -fgcse -fhoist-adjacent-loads -finline-small-functions -fipa-sra -foptimize-sibling-calls -fpeephole2
# -freorder-blocks-and-partition -freorder-functions -frerun-cse-after-loop -fschedule-insns
# -fschedule-insns2 -ftree-pre -ftree-vrp")


set(SOURCE_FILES main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Executable

add_executable(LZW_Archiver ${SOURCE_FILES})

target_link_libraries(LZW_Archiver
                      Archiver
                      )

# Library

add_library(Archiver core.cpp core.h)

set_target_properties(Archiver PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# Unit tests

add_executable(unittest unittest.cpp core.h core.cpp)

target_link_libraries(unittest
                      Archiver
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )

add_test(unittest unittest)


