# Copyright (c) Brandon Pacewic
# SPDX‑License‑Identifier: MIT

BUILD_DIR        ?= build
CMAKE_GENERATOR  ?= Unix Makefiles
BUILD_TESTS      ?= ON        # pass BUILD_TESTS=OFF to skip
BUILD_BENCH      ?= OFF
BUILD_TOOLS      ?= OFF
BUILD_TYPE       ?= Debug     # Release | RelWithDebInfo ...
COMPILE_COMMANDS ?= ON
JOBS             ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu)

CMAKE_FLAGS = \
  -G "$(CMAKE_GENERATOR)" \
  -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
  -DBUILD_TESTING=$(BUILD_TESTS) \
  -DBUILD_BENCHMARKS=$(BUILD_BENCH) \
  -DBUILD_TOOLS=$(BUILD_TOOLS) \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=$(COMPILE_COMMANDS)

.PHONY: build test bench tools \
        format install-hooks clean distclean help

configure:
	@mkdir -p "$(BUILD_DIR)"
	@cmake -S . -B "$(BUILD_DIR)" $(CMAKE_FLAGS)
ifeq ($(COMPILE_COMMANDS),ON)
	@ln -sf "$(BUILD_DIR)/compile_commands.json" compile_commands.json
endif

build: configure
	@cmake --build "$(BUILD_DIR)" -- -j$(JOBS)

test: build
	@ctest --test-dir "$(BUILD_DIR)" --output-on-failure

bench: BUILD_BENCH := ON
bench: build
	@cmake --build "$(BUILD_DIR)" -j$(JOBS)

run-benchmarks: bench
	@cmake --build "$(BUILD_DIR)" --target run_all_benchmarks -- -j$(JOBS)

bench-diff:
	@python tools/scripts/compare_benchmarks.py

bench-out:
	@python tools/scripts/output_benchmarks.py

tools: BUILD_TOOLS := ON
tools: build

format:
	@clang-format -i -style=file $(shell git ls-files '*.hpp' '*.h' '*.cpp')

install-hooks:
	@ln -sf ../../scripts/pre-commit .git/hooks/pre-commit
	@echo "Pre-commit hook installed"

clean:
	@cmake --build "$(BUILD_DIR)" --target clean || true

distclean:
	@rm -rf "$(BUILD_DIR)"
ifeq ($(COMPILE_COMMANDS),ON)
	@rm -f compile_commands.json
endif

help:
	@echo "Targets:"
	@echo "  build              - configure and build"
	@echo "  test               - run ctest (RUN_TESTS=ON)"
	@echo "  bench              - build & run benchmarks (BUILD_BENCH=ON)"
	@echo "  run-benchmarks     - run all benchmarks"
	@echo "  bench-diff         - compare the two most recent benchmark runs"
	@echo "  bench-out          - output the most recent benchmark run"
	@echo "  tools              - build project-defined tools (BUILD_TOOLS=ON)"
	@echo "  format             - run clang-format on all source files"
	@echo "  install-hooks      - install pre-commit hook (calls scripts/lint.sh)"
	@echo "  clean              - clean build artifacts"
	@echo "  distclean          - clean entire build dir"
	@echo ""
	@echo "Knobs (override with VAR=value):"
	@echo "  BUILD_DIR, CMAKE_GENERATOR, BUILD_TYPE, JOBS"
	@echo "  BUILD_TESTS, BUILD_BENCH, BUILD_TOOLS"

# Default to help when running `make` without targets
.DEFAULT_GOAL := help
