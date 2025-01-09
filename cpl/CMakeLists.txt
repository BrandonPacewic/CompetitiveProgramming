# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(cpl ${SOURCES})
target_include_directories(cpl PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

include_directories(BEFORE ${CMAKE_CURRENT_LIST_DIR}/inc)
