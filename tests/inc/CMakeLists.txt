# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

set(TESTS
    {CMAKE_CURRENT_SOURCE_DIR}/output_container/test.cpp
)

add_executable(output_container ${CMAKE_CURRENT_SOURCE_DIR}/output_container/test.cpp)

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/cpl/inc)
