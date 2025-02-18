# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.23)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(competitive_programming_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tools EXCLUDE_FROM_ALL)
add_subdirectory(benchmarks EXCLUDE_FROM_ALL)
add_subdirectory(cpl)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    enable_testing()
    add_subdirectory(tests)
endif()
