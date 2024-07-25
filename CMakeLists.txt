cmake_minimum_required(VERSION 3.5.0)
project(sct-mem-api VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY out/release/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out/release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY out/release)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY out/debug/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out/debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY out/debug)
endif()

add_subdirectory(example_program)

add_library(sct-mem-api STATIC src/sct-mem-api.c)