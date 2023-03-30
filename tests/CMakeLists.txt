# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

add_subdirectory(cpl)

find_package(Python "3.11" REQUIRED COMPONENTS Interpreter)
add_test(NAME PythonStaticTesting COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/run_tests.py ${CMAKE_SOURCE_DIR})
