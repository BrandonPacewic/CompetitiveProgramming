# Implementation plan

## Completed

#### Phase 1: Core Infrastructure
- [x] 1.1 Create top-level Makefile with version, V=, O= handling
- [x] 1.2 Create scripts/Kbuild.include with core macros
- [x] 1.3 Create scripts/Makefile.build for recursive building
- [x] 1.4 Create scripts/Makefile.lib with CXX compilation rules
- [x] 1.5 Create scripts/Makefile.clean for clean recursion
- [x] 1.6 Implement GCC -MD/-MP dependency generation
- [x] 1.7 Implement V=0/1 verbosity with quiet_cmd_*/cmd_* pattern

## In Progress

## Pending

### Kbuild System (kbuild-system.md)

#### Phase 2: Kconfig Integration
- [x] 2.1 Add kconfig-frontends as git submodule
- [x] 2.2 Create top-level Kconfig file
- [x] 2.3 Create cpl/Kconfig with per-module options
- [x] 2.4 Create tests/Kconfig with per-test options
- [x] 2.5 Create benchmarks/Kconfig with benchmark options
- [x] 2.6 Create tools/Kconfig with tool options
- [x] 2.7 Implement menuconfig target
- [x] 2.8 Implement auto.conf and autoconf.h generation
- [x] 2.9 Create configs/ directory with preset configs

#### Phase 3: Per-Directory Kbuild Files
- [x] 3.1 Create cpl/Kbuild with obj-y for library sources
- [x] 3.2 Create tests/Kbuild with test-y and subdir handling
- [x] 3.3 Create individual tests/cpl/*/Kbuild for each test
- [x] 3.4 Create benchmarks/Kbuild with bench-y
- [x] 3.5 Create benchmarks/cpl/*/Kbuild for each benchmark
- [x] 3.6 Create tools/Kbuild with tool-y
- [x] 3.7 Create tools/graph_casegen/Kbuild

#### Phase 4: Test Runner
- [x] 4.1 Implement make test aggregate target
- [x] 4.2 Implement make test-<name> individual targets
- [x] 4.3 Add test result reporting (PASS/FAIL summary)
- [x] 4.4 Support TEST= variable for filtering

#### Phase 5: Benchmark Integration
- [x] 5.1 Integrate Google Benchmark submodule via Kbuild
- [x] 5.2 Implement make bench target

#### Phase 6: Install and Utilities
- [x] 6.1 Implement make install for headers
- [x] 6.2 Implement make clean, distclean, mrproper
- [x] 6.3 Implement make help with categorized output
- [x] 6.4 Implement make format (clang-format wrapper)

#### Phase 7: Cross-Compilation
- [x] 7.1 Implement CROSS_COMPILE= prefix handling
- [x] 7.2 Test cross-compilation with different toolchains

#### Phase 8: Documentation and Polish
- [x] 8.1 Update project README.md with new build instructions
- [x] 8.2 Add BUILD.md with detailed Kbuild documentation
- [x] 8.3 Ensure CMake still works as fallback
- [x] 8.4 Update .gitignore for new generated files

#### Phase 9: Bug Fixes
- [x] 9.1 Fix missing tests/include path in CPLINCLUDES for test compilation
