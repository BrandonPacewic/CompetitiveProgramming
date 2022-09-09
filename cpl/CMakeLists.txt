# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/container.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/ecmath.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/matrix.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/output_empty_matrix.cpp
)

add_library(cpl ${SOURCES})

include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/inc")
