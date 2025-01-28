#!/bin/sh

# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

if [ -d "build" ]; then
    rm -rf build/
fi

mkdir build/
cd build/
cmake -G "Unix Makefiles" ../
make
ctest --output-on-failure
