# Implementation plan

## Completed

## In Progress

## Pending

### Kbuild System (kbuild-system.md)

#### Phase 1: Core Infrastructure
- [ ] 1.1 Create top-level Makefile with version, V=, O= handling
- [ ] 1.2 Create scripts/Kbuild.include with core macros
- [ ] 1.3 Create scripts/Makefile.build for recursive building
- [ ] 1.4 Create scripts/Makefile.lib with CXX compilation rules
- [ ] 1.5 Create scripts/Makefile.clean for clean recursion
- [ ] 1.6 Implement GCC -MD/-MP dependency generation
- [ ] 1.7 Implement V=0/1 verbosity with quiet_cmd_*/cmd_* pattern

#### Phase 2: Kconfig Integration
- [ ] 2.1 Add kconfig-frontends as git submodule
- [ ] 2.2 Create top-level Kconfig file
- [ ] 2.3 Create cpl/Kconfig with per-module options
- [ ] 2.4 Create tests/Kconfig with per-test options
- [ ] 2.5 Create benchmarks/Kconfig with benchmark options
- [ ] 2.6 Create tools/Kconfig with tool options
- [ ] 2.7 Implement menuconfig target
- [ ] 2.8 Implement auto.conf and autoconf.h generation
- [ ] 2.9 Create configs/ directory with preset configs

#### Phase 3: Per-Directory Kbuild Files
- [ ] 3.1 Create cpl/Kbuild with obj-y for library sources
- [ ] 3.2 Create tests/Kbuild with test-y and subdir handling
- [ ] 3.3 Create individual tests/cpl/*/Kbuild for each test
- [ ] 3.4 Create benchmarks/Kbuild with bench-y
- [ ] 3.5 Create benchmarks/cpl/*/Kbuild for each benchmark
- [ ] 3.6 Create tools/Kbuild with tool-y
- [ ] 3.7 Create tools/graph_casegen/Kbuild

#### Phase 4: Test Runner
- [ ] 4.1 Implement make test aggregate target
- [ ] 4.2 Implement make test-<name> individual targets
- [ ] 4.3 Add test result reporting (PASS/FAIL summary)
- [ ] 4.4 Support TEST= variable for filtering

#### Phase 5: Benchmark Integration
- [ ] 5.1 Integrate Google Benchmark submodule via Kbuild
- [ ] 5.2 Implement make bench target
- [ ] 5.3 Implement make bench-diff for comparison

#### Phase 6: Install and Utilities
- [ ] 6.1 Implement make install for headers
- [ ] 6.2 Implement make clean, distclean, mrproper
- [ ] 6.3 Implement make help with categorized output
- [ ] 6.4 Implement make format (clang-format wrapper)

#### Phase 7: Cross-Compilation
- [ ] 7.1 Implement CROSS_COMPILE= prefix handling
- [ ] 7.2 Test cross-compilation with different toolchains

#### Phase 8: Documentation and Polish
- [ ] 8.1 Update project README.md with new build instructions
- [ ] 8.2 Add BUILD.md with detailed Kbuild documentation
- [ ] 8.3 Ensure CMake still works as fallback
- [ ] 8.4 Update .gitignore for new generated files
