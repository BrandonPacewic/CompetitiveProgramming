# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.23)
project(competitive_programming_library_graph_casegen LANGUAGES CXX)

add_executable(graph_casegen graph_casegen.cpp)
set_target_properties(graph_casegen PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools/graph_casegen)
target_link_libraries(graph_casegen PRIVATE cpl)
target_include_directories(graph_casegen PRIVATE ${CMAKE_SOURCE_DIR}/cpl/inc)
