# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.23)
project(competitive_programming_library_benchmarks LANGUAGES CXX)

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/benchmark/.git")
    message(FATAL_ERROR "google-benchmark is not checked out; make sure to run\n    git submodule update --init benchmarks/benchmark")
endif()

set(BENCHMARK_ENABLE_DOXYGEN OFF)
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)

if(APPLE)
    set(HAVE_LIB_RT OFF)
endif()

add_subdirectory(benchmark)

set(BENCHMARK_DIR "${CMAKE_CURRENT_LIST_DIR}/cpl")
set(BENCHMARK_ROOT_DIR "${CMAKE_SOURCE_DIR}/benchmarks")
file(GLOB_RECURSE BENCHMARK_FILES "${BENCHMARK_DIR}/*.cpp")

set(BENCHMARK_BINARY_DIR "${CMAKE_BINARY_DIR}/benchmarks")

foreach(BENCHMARK_FILE ${BENCHMARK_FILES})
    get_filename_component(BENCHMARK_NAME_WITH_EXT ${BENCHMARK_FILE} NAME)
    string(REGEX REPLACE "\\.cpp$" "" BENCHMARK_NAME ${BENCHMARK_NAME_WITH_EXT})

    file(RELATIVE_PATH RELATIVE_PATH ${BENCHMARK_ROOT_DIR} ${BENCHMARK_FILE})
    string(REPLACE "/" "_" RELATIVE_TARGET_PREFIX ${RELATIVE_PATH})

    string(REPLACE "." "_" BENCHMARK_TARGET_NAME ${BENCHMARK_NAME})
    set(FINAL_TARGET_NAME "${RELATIVE_TARGET_PREFIX}")

    set(BENCHMARK_BINARY_PATH "${BENCHMARK_BINARY_DIR}/${FINAL_TARGET_NAME}")

    add_executable(${FINAL_TARGET_NAME} ${BENCHMARK_FILE})
    set_target_properties(${FINAL_TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BENCHMARK_BINARY_DIR})
    target_link_libraries(${FINAL_TARGET_NAME} PRIVATE cpl benchmark::benchmark)
endforeach()

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/cpl/inc)
