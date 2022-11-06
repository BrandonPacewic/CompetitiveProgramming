# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.23)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(competitive_programming_library LANGUAGES CXX)

# Set the MSVC C++ Compiler to c++20
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
else()
	message(FATAL_ERROR "Error in CPL usage; Expected MSVC")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cpl)

if(INCLUDE_PSL)
    add_subdirectory(psl)
endif()

# ctest --test-dir build -V
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
