#!/bin/sh

# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

if [ ! -d "build" ]; then
    mkdir build
fi

cd build/
cmake -G "Unix Makefiles" ../
make
