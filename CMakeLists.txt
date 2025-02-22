# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.23)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(competitive_programming_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_BENCHMARKS "Build benchmarks" OFF)

# Should almost* always build tests to verify correctness, regardless of if you intend to run them or not.
# Only case where this should be omitted is if you are building this library as a dependency where
# correctness can be assumed.
option(BUILD_TESTING "Build tests" ON)
option(BUILD_TOOLS "Build tools" OFF)

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(cpl)
