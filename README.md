<h1>
<p align="center">
  C++ Competitive Programming Library
</h1>
    <p align="center">
        <a href="#about">About</a> •
        <a href="#getting-started">Getting Started</a> •
        <a href="#milestones">Milestones</a>
    </p>
</p>

## About

This is my personal C++ library designed specifically for competitive programming. It contains a variety
of data structures, algorithms, and other utilities commonly used in competitive programming. Each component
of this library is designed to be drop-in usable—no setup or external dependencies required. The entire
library is designed to have sections that are copy-pasteable into a single file for contest submission.

## Getting Started

### Quick Start

Clone the repository and its submodules:

```bash
git clone --recursive https://github.com/BrandonPacewic/CompetitiveProgramming
cd CompetitiveProgramming
```

Build the library, tests, and tools:

```bash
make                # Build everything with default configuration
make test           # Run all tests
make bench          # Run benchmarks (optional)
```

### Build System

This project uses a Linux kernel-style **Kbuild** build system, providing powerful configuration and build management:

#### Configuration

Configure which components to build using one of these methods:

```bash
make menuconfig          # Interactive configuration menu (ncurses)
make defconfig           # Default configuration (recommended)
make debug_defconfig     # Debug build with sanitizers
make release_defconfig   # Optimized release build
make minimal_defconfig   # Minimal library only
```

The configuration is saved to `.config` and controls which algorithms, data structures, tests, and tools are compiled.

#### Building

```bash
make                     # Build library, tests, and tools
make cpl                 # Build only the CPL library
make tests               # Build only tests
make benchmarks          # Build only benchmarks
make tools               # Build only tools

make V=1                 # Verbose build (show full commands)
make O=build             # Out-of-tree build to build/ directory
```

#### Testing

```bash
make test                # Run all enabled tests
make test-disjoint_set   # Run a specific test
make TEST=container_*    # Run tests matching pattern
```

Each test shows `PASS` or `FAIL` with execution time.

#### Benchmarking

```bash
make bench               # Run all enabled benchmarks
make bench-merge_sort    # Run a specific benchmark
make BENCH=*_sort        # Run benchmarks matching pattern
```

#### Other Targets

```bash
make format              # Format C++ code with clang-format
make install             # Install headers to PREFIX/include/cpl/
make clean               # Remove generated files (keep config)
make mrproper            # Remove all generated files + config
make help                # Show all available targets
```

#### Cross-Compilation

To cross-compile for a different architecture:

```bash
make CROSS_COMPILE=aarch64-linux-gnu-
```

### Usage in Competitive Programming

Since the core idea of this library is to copy-paste sections into your own code, you can:

1. **Direct copy-paste**: Copy code from `cpl/inc` and `cpl/src` into your submission.
2. **Local includes**: Include headers locally for practice and testing.
3. **Test your implementations**: Use `make test` to verify algorithm correctness.
4. **Benchmark performance**: Use `make bench` to compare algorithm efficiency.

> [!TIP]
> Use `make menuconfig` to enable only the algorithms you need, keeping compile times fast during practice.

> [!NOTE]
> CMake is still supported as a fallback build system. See `Makefile.cmake` for details.

## Milestones

As with every single one of my projects, this is still very much a work in progress. The following is a list
of goals I have for this project before I consider it to be complete, in no particular order:

|  #  | Goal                                                      | Status |
| :-: | --------------------------------------------------------- | :----: |
|  1  | Refactor old code to match current standards              |   ⚠️   |
|  2  | Full test coverage                                        |   ⚠️   |
|  3  | Performance with supporting benchmarks                    |   ⚠️   |
|  4  | Codebase Atomizer                                         |   ❌   |
|  5  | Full implementation of the CPH                            |   ❌️   |

A more detailed description of each goal can be found below:

### Refactor Old Code to Match Current Standards

This is my longest standing project in terms of the initial creation date. As such, the earlier code does
not reflect my current standards. One of the current goals is to revise such code to improve quality.

> [!NOTE]
> I find the structure of the code in this repository to be quite volatile. I have probably re-written some
> of the algorithms 10+ times as this library tends to evolve as I become a better programmer.
> If something doesn't look quite right, it probably isn't.

### Full Test Coverage

While this library is meant for competitive programming (where tests don’t carry over), it should still have
full test coverage — including tests derived from problems where I used components of this library to solve them.

### Performance with Supporting Benchmarks

In the spirit of competitive programming, while solving the problem is the main goal, performance is also
a key component. Benchmarks should back up various design decisions when it comes to how I have chosen to
structure and implement various key algorithms and data structures.

> [!NOTE]
> While I do want 100% test coverage, I'm less concerned about benchmarks. Benchmarks will be added
> as I find them necessary to support design decisions.

### Codebase Atomizer

The *Atomizer* is a tool used to break down the codebase into smaller, more manageable pieces, that can be
retrieved quickly. For example, if you want to use a specific function, say `output_container` to keep things
simple. You can use the *Atomizer* output to retrieve that specific function via a file lookup, `output_container.cpp`.
You can also use any supporting tool you want to paste that file buffer directly inline into your code. Rather than
opening the container header file and copying the specific lines from the file that you need. This will also work
with more complex algorithms that may require an additional data structure to function. For example, if you want to
use Kruskal's algorithm, you can use the *Atomizer* to retrieve the `kruskal.cpp` file which will include the
supporting `DisjointSet` class used within the algorithm. Again saving you from finding the specific lines of code
within the header file that you need.

### Full Implementation of the CPH (Competitive Programming Handbook)

The [*Competitive Programming Handbook*](https://cses.fi/book/book.pdf) by Antti Laaksonen is an awesome, all in one,
resource for everything competitive programming. It contains everything from compiling and reading input to sweep line
algorithms including convex hulls. Its an eventual goal of mine to fully implement all the algorithms outlined
in the book. This has the added benefit of an *complete* documentation source of all the algorithms in this
library. This is a long term goal and will likely take a while to complete.

> [!NOTE]
> This is my endgame for this project. When its completed I will consider this project *done* as so far
> as it will no longer be a major work in progress for me personally. I will still add things here and there
> and work on it when I'm compelled to do so but the core goals of this project will be officially complete.

## License

Copyright (c) Brandon Pacewic

SPDX-License-Identifier: MIT
