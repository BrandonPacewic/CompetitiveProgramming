# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

add_subdirectory(inc)

find_package(Python "3.9" REQUIRED COMPONENTS Interpreter)
add_test(NAME PythonStaticTesting COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py ${CMAKE_SOURCE_DIR})
