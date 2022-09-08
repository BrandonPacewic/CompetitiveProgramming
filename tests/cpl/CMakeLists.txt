# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

set(TESTS
    {CMAKE_CURRENT_SOURCE_DIR}/output_container/test.compile.run.cpp
)

set(CPL_CORE_DIR ${CMAKE_SOURCE_DIR}/build/cpl/libcpl.a)
add_library(cpl_core STATIC IMPORTED)
set_target_properties(cpl_core PROPERTIES IMPORTED_LOCATION ${CPL_CORE_DIR})

add_executable(output_container.compile.run.a ${CMAKE_CURRENT_SOURCE_DIR}/output_container/test.compile.run.cpp)
target_link_libraries(output_container.compile.run.a cpl_core)

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/cpl/inc)
