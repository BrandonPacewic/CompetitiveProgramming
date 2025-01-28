# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

set(TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/cpl")
set(TEST_ROOT_DIR "${CMAKE_SOURCE_DIR}/tests")
file(GLOB_RECURSE TEST_FILES "${TEST_DIR}/*.cpp")

set(TEST_BINARY_DIR "${CMAKE_BINARY_DIR}/tests")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME_WITH_EXT ${TEST_FILE} NAME)
    string(REGEX REPLACE "\\.cpp$" "" TEST_NAME ${TEST_NAME_WITH_EXT})

    file(RELATIVE_PATH RELATIVE_PATH ${TEST_ROOT_DIR} ${TEST_FILE})
    string(REPLACE "/" "_" RELATIVE_TARGET_PREFIX ${RELATIVE_PATH})

    string(REPLACE "." "_" TEST_TARGET_NAME ${TEST_NAME})
    set(FINAL_TARGET_NAME "${RELATIVE_TARGET_PREFIX}")

    set(TEST_BINARY_PATH "${TEST_BINARY_DIR}/${FINAL_TARGET_NAME}")

    add_executable(${FINAL_TARGET_NAME} ${TEST_FILE})
    set_target_properties(${FINAL_TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_BINARY_DIR})

    add_test(NAME ${FINAL_TARGET_NAME} COMMAND ${TEST_BINARY_PATH})
    message(STATUS "Registered test: ${FINAL_TARGET_NAME} with path ${TEST_BINARY_PATH}")
endforeach()

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/cpl/inc)
