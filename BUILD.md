# BUILD.md - CPL Kbuild System Documentation

This document provides comprehensive documentation for the CPL (Competitive Programming Library) build system, which uses a Linux kernel-style **Kbuild** architecture.

## Table of Contents

1. [Overview](#overview)
2. [Quick Start](#quick-start)
3. [Configuration System](#configuration-system)
4. [Build Targets](#build-targets)
5. [Testing and Benchmarking](#testing-and-benchmarking)
6. [Advanced Features](#advanced-features)
7. [Adding New Components](#adding-new-components)
8. [Build System Internals](#build-system-internals)
9. [Troubleshooting](#troubleshooting)

---

## Overview

### What is Kbuild?

Kbuild is the build system used by the Linux kernel, providing:

- **Configuration management** via Kconfig (similar to `make menuconfig`)
- **Recursive make** architecture for modular builds
- **Automatic dependency tracking** using GCC's `-MD/-MP` flags
- **Out-of-tree builds** via `O=` parameter
- **Verbosity control** with `V=0/1/2` for debugging builds
- **Cross-compilation** support via `CROSS_COMPILE` prefix

### Why Kbuild for CPL?

For a competitive programming library, Kbuild provides several advantages:

1. **Selective compilation**: Enable only the algorithms/tests you need via configuration
2. **Fast incremental builds**: Automatic dependency tracking rebuilds only what changed
3. **Modular structure**: Each component (library, test, benchmark, tool) is independent
4. **Familiar for kernel developers**: Uses the same patterns as the Linux kernel
5. **No external dependencies**: Pure Make + Python 3 (for Kconfig)

### Architecture Overview

```
CompetitiveProgramming/
├── Makefile              # Top-level Makefile (entry point)
├── Kconfig              # Top-level configuration menu
├── .config              # Current configuration (generated)
├── configs/             # Preset configurations
│   ├── defconfig        # Default configuration
│   ├── debug_defconfig  # Debug build
│   └── release_defconfig # Release build
├── scripts/             # Kbuild infrastructure
│   ├── Kbuild.include   # Core macros
│   ├── Makefile.build   # Recursive build logic
│   ├── Makefile.lib     # C++ compilation rules
│   └── Makefile.clean   # Cleaning logic
├── cpl/                 # Library source
│   ├── Kbuild           # Library build file
│   ├── Kconfig          # Library configuration options
│   └── built-in.a       # Compiled library archive
├── tests/               # Test suite
│   ├── Kbuild           # Test aggregation
│   ├── Kconfig          # Test configuration
│   └── cpl/*/Kbuild     # Per-test build files
├── benchmarks/          # Benchmark suite
│   ├── Kbuild
│   ├── Kconfig
│   └── cpl/*/Kbuild
└── tools/               # Utility tools
    ├── Kbuild
    └── Kconfig
```

---

## Quick Start

### Basic Usage

```bash
# Clone with submodules (includes kconfig-frontends and Google Benchmark)
git clone --recursive https://github.com/BrandonPacewic/CompetitiveProgramming
cd CompetitiveProgramming

# Configure (first time or after changing requirements)
make defconfig           # Default balanced configuration
# OR
make menuconfig          # Interactive configuration menu

# Build everything
make                     # Build library, tests, and tools

# Run tests
make test                # Run all enabled tests
make test-disjoint_set   # Run specific test

# Run benchmarks
make bench               # Run all enabled benchmarks
make bench-merge_sort    # Run specific benchmark
```

### Common Workflows

**Development Workflow** (frequent recompilation):
```bash
make defconfig          # Enable most features
make V=1                # Verbose build to see full commands
make test               # Verify correctness
```

**Release Workflow** (optimization):
```bash
make release_defconfig  # Optimized, no debug info
make
make install            # Install headers to /usr/local/include/cpl/
```

**Minimal Workflow** (contest practice):
```bash
make minimal_defconfig  # Library only, no tests/tools
make cpl                # Build just the library
```

---

## Configuration System

### Configuration Files

The configuration system is based on **Kconfig**, the same system used in the Linux kernel.

**Configuration file**: `.config` (generated, do not edit manually)
**Configuration source**: `Kconfig` files throughout the tree

### Configuration Targets

| Target | Description |
|--------|-------------|
| `make menuconfig` | Interactive ncurses-based configuration menu |
| `make defconfig` | Load default configuration (balanced, most features enabled) |
| `make debug_defconfig` | Debug configuration (sanitizers, debug symbols, no optimization) |
| `make release_defconfig` | Release configuration (maximum optimization, stripped) |
| `make minimal_defconfig` | Minimal configuration (library only, no tests/tools) |
| `make allnoconfig` | Disable all optional features |
| `make allyesconfig` | Enable all optional features |
| `make syncconfig` | Regenerate `auto.conf` and `autoconf.h` from `.config` |

### Using menuconfig

```bash
make menuconfig
```

This opens an interactive menu where you can:
- Navigate with arrow keys
- Press `Space` to toggle options
- Press `/` to search for options
- Press `?` to view help for the selected option
- Press `Esc Esc` or select `Exit` to save and quit

### Configuration Options

The configuration menu is organized into sections:

**Build Targets**:
- Which tests to compile (`CONFIG_TEST_*`)
- Which benchmarks to compile (`CONFIG_BENCH_*`)
- Which tools to compile (`CONFIG_TOOL_*`)

**Compiler Options**:
- Optimization level (`CONFIG_CC_OPTIMIZE_FOR_PERFORMANCE`, `CONFIG_CC_OPTIMIZE_FOR_SIZE`)
- Debug information (`CONFIG_DEBUG_INFO`)
- Sanitizers (`CONFIG_ASAN`, `CONFIG_UBSAN`)
- Release mode (`CONFIG_RELEASE`)

**Library Modules**:
- Which library components to include

### Generated Files

When you run a configuration target, the build system generates:

- `.config` - Your configuration choices
- `include/config/auto.conf` - Makefile-compatible configuration variables
- `include/config/autoconf.h` - C/C++ header with `#define` macros

These files are automatically regenerated when `.config` changes.

---

## Build Targets

### Primary Targets

| Target | Description |
|--------|-------------|
| `make` or `make all` | Build library, tests, and tools (default target) |
| `make cpl` | Build only the CPL library |
| `make tests` | Build only the test suite |
| `make benchmarks` | Build only the benchmarks |
| `make tools` | Build only the tools |

### Build Control Variables

**Verbosity**:
```bash
make V=0                # Quiet build (default) - shows only "CXX file.o"
make V=1                # Verbose build - shows full compiler commands
make V=2                # Debug build - shows reason for rebuilding each target
```

**Out-of-tree builds**:
```bash
make O=build            # Build in ./build/ directory instead of source tree
make O=/tmp/cpl-build   # Build in /tmp/cpl-build/
```

Benefits of out-of-tree builds:
- Keep source tree clean
- Build multiple configurations simultaneously (e.g., debug + release)
- Easier to clean (just delete the output directory)

**Cross-compilation**:
```bash
make CROSS_COMPILE=aarch64-linux-gnu-   # Cross-compile for ARM64
make CROSS_COMPILE=arm-linux-gnueabi-   # Cross-compile for ARM
```

The `CROSS_COMPILE` prefix is prepended to all toolchain commands:
- `CROSS_COMPILE=aarch64-linux-gnu-` → `aarch64-linux-gnu-g++`, `aarch64-linux-gnu-ar`, etc.

**Parallel builds**:
```bash
make -j$(nproc)         # Use all CPU cores
make -j8                # Use 8 parallel jobs
```

### Build Output

**Library**: `cpl/built-in.a` - Static archive containing all library code

**Tests**: `tests/cpl/*/test` - One test executable per test directory

**Benchmarks**: `benchmarks/cpl/*/bench` - One benchmark executable per benchmark directory

**Tools**: `tools/*/tool` - Utility executables

### Cleaning Targets

| Target | Description |
|--------|-------------|
| `make clean` | Remove generated files (keep configuration) |
| `make mrproper` | Remove all generated files + configuration |
| `make distclean` | `mrproper` + remove editor backups and patches |

**What gets removed**:
- `make clean`: `*.o`, `*.a`, `*.d`, `*.cmd`, executables
- `make mrproper`: Everything in `clean` + `.config`, `include/config/`, `include/generated/`
- `make distclean`: Everything in `mrproper` + `*.orig`, `*.rej`, `*~`, `*.bak`

---

## Testing and Benchmarking

### Running Tests

**All tests**:
```bash
make test               # Build and run all enabled tests
```

Output format:
```
Running all tests...
========================================
disjoint_set                            PASS
container_merge_sort                    PASS
container_debug_output                  FAIL
========================================
Total: 15  Passed: 14  Failed: 1
Result: FAILED
```

**Specific test**:
```bash
make test-disjoint_set      # Run only the disjoint_set test
make test-container_*       # Run all container tests (pattern matching)
```

**Filter tests**:
```bash
make test TEST=disjoint_set         # Exact match
make test TEST=container_*          # Wildcard pattern
make test TEST=*_mst                # All MST tests
```

### Running Benchmarks

**All benchmarks**:
```bash
make bench              # Build and run all enabled benchmarks
```

**Specific benchmark**:
```bash
make bench-merge_sort       # Run only merge_sort benchmark
```

**Filter benchmarks**:
```bash
make bench BENCH=merge_sort     # Exact match
make bench BENCH=*_sort         # All sorting benchmarks
```

### Test/Benchmark Structure

Each test/benchmark follows the same pattern:

```
tests/cpl/disjoint_set/
├── Kbuild              # Build configuration: obj-$(CONFIG_TEST_DISJOINT_SET) += test.o
├── test.cpp            # Test source (compiled to test.o)
└── test                # Test executable (linked with cpl/built-in.a)
```

Tests are standalone executables that:
- Return 0 on success
- Return non-zero on failure
- Print diagnostic information on failure

---

## Advanced Features

### Dependency Tracking

The build system uses GCC's automatic dependency generation:

```bash
# Compiler flags used internally:
-MD     # Generate .d dependency file alongside .o
-MP     # Add phony targets for each dependency
```

For each compiled file `foo.o`, the build system generates:
- `.foo.o.cmd` - Command used to build `foo.o` (for rebuild detection)
- `.foo.o.d` - Dependencies of `foo.o` (auto-generated by GCC)

**Rebuild detection**:
- Target is rebuilt if the command line changes
- Target is rebuilt if any dependency (source or header) changes
- Target is rebuilt if marked with `FORCE`

**Example**:
```bash
# First build
$ make cpl/src/output_empty_matrix.o
  CXX     cpl/src/output_empty_matrix.o

# No change - no rebuild
$ make cpl/src/output_empty_matrix.o
make: 'cpl/src/output_empty_matrix.o' is up to date.

# Touch header - rebuild
$ touch cpl/inc/container.h
$ make cpl/src/output_empty_matrix.o
  CXX     cpl/src/output_empty_matrix.o
```

### Quiet Command Pattern

The build system uses the `quiet_cmd_*` / `cmd_*` pattern from the Linux kernel:

```makefile
# Define the command
quiet_cmd_cxx_o_cpp = CXX     $@
      cmd_cxx_o_cpp = $(CXX) $(cxx_flags) $(CPPFLAGS) -c -o $@ $<

# Use the command
$(obj)/%.o: $(src)/%.cpp FORCE
	$(call if_changed,cxx_o_cpp)
```

- `quiet_cmd_cxx_o_cpp`: Short message shown when `V=0` (quiet mode)
- `cmd_cxx_o_cpp`: Full command executed
- `if_changed`: Macro that checks if rebuild is needed

This pattern provides:
- Clean output by default (`CXX file.o`)
- Full command visibility with `V=1`
- Consistent formatting across all build operations

### Recursive Make

The build system uses recursive make to descend into subdirectories:

```makefile
# Top-level Makefile
build-cpl:
	$(Q)$(MAKE) $(build)=cpl

# scripts/Makefile.build handles the recursion
# It includes the Kbuild file in the target directory
include $(kbuild-file)
```

**Directory traversal**:
1. Top-level `Makefile` invokes `make $(build)=cpl`
2. `scripts/Makefile.build` is used with `obj=cpl`
3. `cpl/Kbuild` is included, which defines `obj-y`
4. If `cpl/Kbuild` defines `subdir-y`, recursion continues

**Built-in.a aggregation**:
- Each directory with `obj-y` creates a `built-in.a` archive
- Subdirectory `built-in.a` files are aggregated into parent `built-in.a`
- Final `cpl/built-in.a` contains all library code

### Installation

```bash
make install                    # Install to /usr/local/include/cpl/
make install PREFIX=/opt/cpl    # Install to /opt/cpl/include/cpl/
make install DESTDIR=/tmp/pkg   # Stage installation for packaging
```

The install target:
- Creates `$(DESTDIR)$(PREFIX)/include/cpl/`
- Copies all headers from `cpl/inc/*.h`
- Sets permissions to `644` (readable by all, writable by owner)

**Packaging example**:
```bash
make install DESTDIR=/tmp/cpl-package PREFIX=/usr
# Now /tmp/cpl-package/usr/include/cpl/ contains the headers
# Package the contents of /tmp/cpl-package/ into a .deb or .rpm
```

### Code Formatting

```bash
make format             # Format all C++ source and header files
```

The format target:
- Uses `clang-format` with the project's `.clang-format` configuration
- Processes all `*.cpp` and `*.h` files in `cpl/`, `tests/`, and `tools/`
- Excludes submodules (`benchmark/`, `kconfig-frontends/`)
- Respects `V=0/1` for quiet/verbose output

---

## Adding New Components

### Adding a New Library Module

1. **Add source files** to `cpl/src/`:
   ```cpp
   // cpl/src/my_algorithm.cpp
   #include "my_algorithm.h"
   // implementation
   ```

2. **Add header** to `cpl/inc/`:
   ```cpp
   // cpl/inc/my_algorithm.h
   #ifndef MY_ALGORITHM_H
   #define MY_ALGORITHM_H
   // declarations
   #endif
   ```

3. **Update `cpl/Kbuild`**:
   ```makefile
   obj-y += src/my_algorithm.o
   ```

4. **(Optional) Add configuration option** in `cpl/Kconfig`:
   ```kconfig
   config MY_ALGORITHM
       bool "Enable My Algorithm"
       default y
       help
         This enables my custom algorithm implementation.
   ```

5. **Use conditional compilation** (optional):
   ```makefile
   # cpl/Kbuild
   obj-$(CONFIG_MY_ALGORITHM) += src/my_algorithm.o
   ```

### Adding a New Test

1. **Create test directory**:
   ```bash
   mkdir -p tests/cpl/my_algorithm
   ```

2. **Write test source**:
   ```cpp
   // tests/cpl/my_algorithm/test.cpp
   #include "my_algorithm.h"
   #include <cassert>

   int main() {
       // Test cases
       assert(my_algorithm(input) == expected_output);
       return 0;
   }
   ```

3. **Create `tests/cpl/my_algorithm/Kbuild`**:
   ```makefile
   # Copyright (c) Brandon Pacewic
   # SPDX-License-Identifier: MIT

   obj-$(CONFIG_TEST_MY_ALGORITHM) += test.o
   ```

4. **Add configuration option** in `tests/Kconfig`:
   ```kconfig
   config TEST_MY_ALGORITHM
       bool "Test My Algorithm"
       default y
       help
         Test suite for my_algorithm implementation.
   ```

5. **Update configuration and build**:
   ```bash
   make menuconfig      # Enable the new test
   make test-my_algorithm
   ```

### Adding a New Benchmark

1. **Create benchmark directory**:
   ```bash
   mkdir -p benchmarks/cpl/my_algorithm
   ```

2. **Write benchmark source** (using Google Benchmark):
   ```cpp
   // benchmarks/cpl/my_algorithm/bench.cpp
   #include "my_algorithm.h"
   #include <benchmark/benchmark.h>

   static void BM_MyAlgorithm(benchmark::State& state) {
       for (auto _ : state) {
           my_algorithm(data);
       }
   }
   BENCHMARK(BM_MyAlgorithm);

   BENCHMARK_MAIN();
   ```

3. **Create `benchmarks/cpl/my_algorithm/Kbuild`**:
   ```makefile
   # Copyright (c) Brandon Pacewic
   # SPDX-License-Identifier: MIT

   obj-$(CONFIG_BENCH_MY_ALGORITHM) += bench.o
   ```

4. **Add configuration option** in `benchmarks/Kconfig`:
   ```kconfig
   config BENCH_MY_ALGORITHM
       bool "Benchmark My Algorithm"
       default y
       help
         Benchmark suite for my_algorithm performance.
   ```

5. **Update configuration and run**:
   ```bash
   make menuconfig      # Enable the new benchmark
   make bench-my_algorithm
   ```

### Adding a New Tool

1. **Create tool directory**:
   ```bash
   mkdir -p tools/my_tool
   ```

2. **Write tool source**:
   ```cpp
   // tools/my_tool/my_tool.cpp
   #include <iostream>

   int main(int argc, char* argv[]) {
       // Tool implementation
       return 0;
   }
   ```

3. **Create `tools/my_tool/Kbuild`**:
   ```makefile
   # Copyright (c) Brandon Pacewic
   # SPDX-License-Identifier: MIT

   obj-$(CONFIG_TOOL_MY_TOOL) += my_tool.o
   ```

4. **Add configuration option** in `tools/Kconfig`:
   ```kconfig
   config TOOL_MY_TOOL
       bool "Build My Tool"
       default y
       help
         My custom tool for doing XYZ.
   ```

---

## Build System Internals

### Makefile Hierarchy

```
Makefile (top-level)
├── scripts/Kbuild.include     # Core macros (if_changed, cmd, etc.)
├── scripts/Makefile.build     # Recursive build logic
│   ├── scripts/Makefile.lib   # C++ flags and rules
│   └── */Kbuild               # Per-directory build files
├── scripts/Makefile.clean     # Cleaning logic
└── scripts/Makefile.host      # Host programs (unused in CPL)
```

### Key Macros

**`$(call if_changed,cmd_name)`**:
- Check if command line has changed
- Check if target needs rebuilding
- Execute command and record to `.cmd` file

**`$(build)` and `$(clean)`**:
```makefile
build := -f $(srctree)/scripts/Makefile.build obj
clean := -f $(srctree)/scripts/Makefile.clean obj
```
Used as:
```makefile
$(Q)$(MAKE) $(build)=cpl
$(Q)$(MAKE) $(clean)=cpl
```

**`quiet_cmd_*` / `cmd_*`**:
- `quiet_cmd_*`: Short message for quiet mode
- `cmd_*`: Full command to execute
- Automatically selected based on `V=` value

### Build Flow

1. **Top-level `make`**:
   - Reads `Makefile`
   - Handles `O=` (out-of-tree), `V=` (verbosity), `CROSS_COMPILE=`
   - Includes `scripts/Kbuild.include`
   - Ensures `.config` exists (runs `make defconfig` if not)
   - Generates `include/config/auto.conf` from `.config`

2. **Target invocation** (e.g., `make cpl`):
   - Top-level `Makefile` invokes `$(MAKE) $(build)=cpl`
   - This translates to: `make -f scripts/Makefile.build obj=cpl`

3. **Recursive build** (`scripts/Makefile.build`):
   - Sets `src := $(obj)` (source directory = object directory)
   - Includes `include/config/auto.conf` (configuration variables)
   - Includes `scripts/Kbuild.include` (macros)
   - Includes `$(src)/Kbuild` (directory's build file)
   - Includes `scripts/Makefile.lib` (flags and rules)

4. **Per-directory build** (e.g., `cpl/Kbuild`):
   - Defines `obj-y` (list of object files to build)
   - Defines `subdir-y` (list of subdirectories to descend into)
   - `scripts/Makefile.build` processes these variables:
     - For each `*.o` in `obj-y`: Invoke `$(call if_changed,cxx_o_cpp)`
     - For each subdirectory in `subdir-y`: Recurse with `$(build)=subdir`
     - Create `built-in.a` from all `obj-y` objects

5. **Dependency tracking**:
   - GCC generates `.foo.o.d` files (dependencies)
   - Build system generates `.foo.o.cmd` files (command line)
   - `.d` files are included automatically by `scripts/Makefile.build`
   - Rebuilds occur when source, headers, or command changes

### Configuration System Internals

**Kconfig files**:
- Define configuration options (`config FOO`)
- Organize into menus (`menu "Title"`)
- Support dependencies (`depends on`)
- Support defaults (`default y`)

**Configuration tools**:
- `scripts/menuconfig.py`: Interactive ncurses menu
- `scripts/conf.py`: Generate `auto.conf` and `autoconf.h` from `.config`

**Generated files**:
- `.config`: Human-readable configuration (format: `CONFIG_FOO=y`)
- `include/config/auto.conf`: Makefile-compatible (format: `CONFIG_FOO := y`)
- `include/config/autoconf.h`: C/C++ header (format: `#define CONFIG_FOO 1`)

**Usage in Kbuild**:
```makefile
# In Kbuild files
obj-$(CONFIG_FOO) += foo.o
# Expands to:
#   obj-y += foo.o      (if CONFIG_FOO=y in .config)
#   obj- += foo.o       (if CONFIG_FOO is not set, effectively ignored)
```

**Usage in C++ code**:
```cpp
#include <config/autoconf.h>

#ifdef CONFIG_FOO
// Conditional compilation
#endif
```

---

## Troubleshooting

### Build Failures

**Problem**: `make: *** No rule to make target '.config'. Stop.`

**Solution**: Run a configuration target first:
```bash
make defconfig
make
```

---

**Problem**: "Configuration is out of date, please run 'make menuconfig'."

**Solution**: Regenerate configuration files:
```bash
make syncconfig
# OR
make defconfig
```

---

**Problem**: Changes to source code not reflected in build

**Solution**: Clean and rebuild:
```bash
make clean
make
```

If dependencies are broken, use `mrproper`:
```bash
make mrproper
make defconfig
make
```

---

**Problem**: Parallel build (`make -j`) fails with strange errors

**Solution**: Try a sequential build to see the real error:
```bash
make -j1 V=1
```

### Configuration Issues

**Problem**: `menuconfig` shows "command not found"

**Solution**: Ensure Python 3 is installed:
```bash
python3 --version
# Install if needed (Debian/Ubuntu):
sudo apt-get install python3
```

---

**Problem**: Changes in `menuconfig` not taking effect

**Solution**: Ensure configuration was saved and regenerated:
```bash
make menuconfig    # Save and exit with "Yes"
make syncconfig    # Regenerate auto.conf
make clean         # Clean old build artifacts
make               # Rebuild
```

### Cross-Compilation Issues

**Problem**: `CROSS_COMPILE` prefix not working

**Solution**: Verify toolchain is installed and in `PATH`:
```bash
which aarch64-linux-gnu-g++
# Install if needed (Debian/Ubuntu):
sudo apt-get install g++-aarch64-linux-gnu
```

---

**Problem**: Tests fail on target architecture

**Solution**: Copy binaries to target system and run there, or use QEMU:
```bash
# On host
make CROSS_COMPILE=aarch64-linux-gnu-
scp tests/cpl/disjoint_set/test target:/tmp/

# On target (or via QEMU)
/tmp/test
```

### Cleaning Issues

**Problem**: `make clean` doesn't remove all generated files

**Solution**: Use `mrproper` for a complete clean:
```bash
make mrproper
```

---

**Problem**: Out-of-tree build directory not cleaned

**Solution**: Manually remove the output directory:
```bash
rm -rf build/
# OR
make O=build mrproper
```

### General Tips

- **Use `V=1`** to see full compiler commands and diagnose build issues
- **Use `V=2`** to see why targets are being rebuilt
- **Use `-j1`** for sequential builds when debugging parallel build issues
- **Use `make help`** to see all available targets
- **Check `.config`** to verify your configuration options
- **Check `.cmd` files** to see what command was used to build a target
- **Check `.d` files** to see what dependencies a target has

### Getting Help

If you encounter issues not covered here:

1. Check the top-level `Makefile` comments
2. Read the relevant `scripts/Makefile.*` file
3. Examine working examples in existing tests/benchmarks
4. Run with `V=1` to see exactly what commands are failing
5. Check that `.config` contains expected values

---

## Appendix: Example Files

### Example Kbuild File

```makefile
# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

# Build this module if CONFIG_MY_MODULE is enabled
obj-$(CONFIG_MY_MODULE) += my_module.o

# Multi-file object (my_module.o is built from these):
my_module-objs := file1.o file2.o file3.o

# Always build this object
obj-y += always_built.o

# Descend into subdirectories
subdir-y += subdir1 subdir2
```

### Example Kconfig File

```kconfig
menu "My Module"
    config MY_MODULE
        bool "Enable My Module"
        default y
        help
          This enables my custom module.

          If unsure, say Y.

    config MY_MODULE_DEBUG
        bool "Enable My Module Debug Output"
        depends on MY_MODULE
        help
          Enable verbose debug output for my module.

          Say Y only for debugging.
endmenu
```

### Example Test File

```cpp
// tests/cpl/my_algorithm/test.cpp
// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include "my_algorithm.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing my_algorithm..." << std::endl;

    // Test case 1
    assert(my_algorithm({1, 2, 3}) == 6);

    // Test case 2
    assert(my_algorithm({}) == 0);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```

### Example Benchmark File

```cpp
// benchmarks/cpl/my_algorithm/bench.cpp
// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include "my_algorithm.h"
#include <benchmark/benchmark.h>
#include <vector>

static void BM_MyAlgorithm_Small(benchmark::State& state) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    for (auto _ : state) {
        benchmark::DoNotOptimize(my_algorithm(data));
    }
}
BENCHMARK(BM_MyAlgorithm_Small);

static void BM_MyAlgorithm_Large(benchmark::State& state) {
    std::vector<int> data(1000000, 1);
    for (auto _ : state) {
        benchmark::DoNotOptimize(my_algorithm(data));
    }
}
BENCHMARK(BM_MyAlgorithm_Large);

BENCHMARK_MAIN();
```

---

## Summary

The CPL Kbuild system provides a powerful, modular, and maintainable build infrastructure for competitive programming. Key takeaways:

- **Configuration-driven**: Use `menuconfig` to control what gets built
- **Automatic dependencies**: Changes to headers automatically trigger rebuilds
- **Modular structure**: Each component (library, test, benchmark) is independent
- **Extensible**: Easy to add new algorithms, tests, and tools
- **Developer-friendly**: Clear output, verbose mode for debugging, out-of-tree builds

For additional help or to report issues, see the project repository:
https://github.com/BrandonPacewic/CompetitiveProgramming
