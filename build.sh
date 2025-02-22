#!/bin/sh

# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

set -e

BUILD_DIR="build"
BUILD_TESTS=ON
RUN_TESTS=OFF
BUILD_BENCH=OFF
BUILD_TOOLS=OFF
CMAKE_GENERATOR="Unix Makefiles"

while [ $# -gt 0 ]; do
    case "$1" in
        --clean)
            rm -rf "$BUILD_DIR"
            shift
            ;;
        --build-tests)
            BUILD_TESTS=OFF
            shift
            ;;
        --test)
            RUN_TESTS=ON
            shift
            ;;
        --bench)
            BUILD_BENCH=ON
            shift
            ;;
        --tools)
            BUILD_TOOLS=ON
            shift
            ;;
        --build-dir=*)
            BUILD_DIR="${1#*=}"
            shift
            ;;
        --help)
            echo "Usage: $0 [--clean] [--build-tests] [--test] [--bench] [--tools] [--build-dir=<dir>] [--help]"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -G "$CMAKE_GENERATOR" \
      -DBUILD_TESTING="$BUILD_TESTS" \
      -DBUILD_BENCHMARKS="$BUILD_BENCH" \
      -DBUILD_TOOLS="$BUILD_TOOLS" \
      ..

make

if [ "$RUN_TESTS" = "ON" ]; then
    ctest --output-on-failure
fi
