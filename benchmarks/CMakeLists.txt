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

    list(APPEND BENCHMARK_TARGETS ${FINAL_TARGET_NAME})
endforeach()

execute_process(
  COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(TIMESTAMP TODAY "%Y-%m-%d_%H-%M-%S")
set(RESULT_DIR "${CMAKE_BINARY_DIR}/benchmarks/results")
file(MAKE_DIRECTORY "${RESULT_DIR}")
set(BENCH_JSONS "")

foreach(TGT IN LISTS BENCHMARK_TARGETS)
  set(JSON_OUT "${RESULT_DIR}/${TODAY}_${GIT_HASH}_${TGT}.json")

    add_custom_command(
    OUTPUT  "${JSON_OUT}"
    COMMAND ${CMAKE_COMMAND} -E echo "→ running ${TGT}"
    COMMAND $<TARGET_FILE:${TGT}>
            --benchmark_out=${JSON_OUT}
            --benchmark_out_format=json
    DEPENDS ${TGT}
    COMMENT "Running benchmark '${TGT}' and writing ${JSON_OUT}"
    VERBATIM
    )

  list(APPEND BENCH_JSONS "${JSON_OUT}")
endforeach()

add_custom_target(run_all_benchmarks ALL DEPENDS ${BENCH_JSONS})

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/cpl/inc)
