# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

set(TESTS
    {CMAKE_CURRENT_SOURCE_DIR}/output_container/test.compile.run.cpp
    {CMAKE_CURRENT_SOURCE_DIR}/container_encoding/test.compile.run.cpp
    {CMAKE_CURRENT_SOURCE_DIR}/container_to_set_conversions/test.compile.run.cpp
    {CMAKE_CURRENT_SOURCE_DIR}/container_alternating_insertion/test.compile.run.cpp
)

set(CPL_CORE_DIR ${CMAKE_SOURCE_DIR}/build/cpl/libcpl.a)
add_library(cpl_core STATIC IMPORTED)
set_target_properties(cpl_core PROPERTIES IMPORTED_LOCATION ${CPL_CORE_DIR})

add_executable(container_to_set_conversions.compile.run.a ${CMAKE_CURRENT_SOURCE_DIR}/container_to_set_conversions/test.compile.run.cpp)
target_link_libraries(container_to_set_conversions.compile.run.a cpl_core)

add_executable(container_encoding.compile.run.a ${CMAKE_CURRENT_SOURCE_DIR}/container_encoding/test.compile.run.cpp)
target_link_libraries(container_encoding.compile.run.a cpl_core)

add_executable(container_alternating_insertion.compile.run.a ${CMAKE_CURRENT_SOURCE_DIR}/container_alternating_insertion/test.compile.run.cpp)
target_link_libraries(container_alternating_insertion.compile.run.a cpl_core)

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/cpl/inc)
