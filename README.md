<h1>
<p align="center">
  C++ Competitive Programming Library
</h1>
    <p align="center">
        <a href="#about">About</a> •
        <a href="#getting-started">Getting Started</a> •
        <a href="#Milestones">Milestones</a>
    </p>
</p>

## About

This is my personal C++ library designed specifically for competitive programming. It contains a variety
of data structures, algorithms, and other utilities commonly used in competitive programming. Each component
of this library is designed to be drop-in-usable—no setup or external dependencies required. The entire
library is designed to have sections that are copy-pasteable into a single file for contest submission.

## Getting Started

Since the core idea of this library is to copy paste sections from it into your own code I recommend
having a local copy of the library in an easy to access location:

```bash
git clone https://github.com/BrandonPacewic/CompetitiveProgramming
```

From there you can:

1. Directly copy code from `cpl/inc` and `cpl/src` into your own code.
2. Include them locally in your own code for local practice.
3. Test against the provided test cases in `test/` for your own algorithm development.

> [!NOTE]
> Additional instructions and support for importing the library and using the test cases is
> planed to be added in the future.

## Milestones

As will every single one of my projects, this is still very much a work in progress. The following is a list
of goals I have for this project before I'm truly happy with it, in no particular order:

|  #  | Goal                                                      | Status |
| :-: | --------------------------------------------------------- | :----: |
|  1  | Refactor old code to match current standards              |   ⚠️   |
|  2  | Full test coverage                                        |   ⚠️   |
|  3  | Performance with supporting benchmarks                    |   ⚠️   |
|  4  | Codebase Atomizer                                         |   ❌   |
|  5  | Full implementation of the CPH                            |   ❌️   |

A more detailed description of each goal can be found below:

#### Refactor Old Code to Match Current Standards

This is my longest standing project in terms of the initial creation date. As such, the earlier code does
not reflect my current standards. One of the current goals is to revise such code to improve quality.

> [!WARNINg]
> I find the structure of the code in this repository to be quite volatile. I have probably re-written some
> of the algorithms 10+ times. If something doesn't look quite right, it probably isn't.

#### Full Test Coverage

While this library is designed to be used in competitive programming, where tests written in this repository
obviously won't be carried over. There still should be total test coverage this includes copies of various
programming problems that I have used sections of this library to solve.

#### Performance with Supporting Benchmarks

In the spirit of competitive programming, while solving the problem is the main goal, performance is also
a key component. Benchmarks should back up various design decisions when it comes to how I have chosen to
structure and implement various key algorithms and data structures.

> [!NOTE]
> While I do want 100% test coverage, I'm less concerned about benchmarks. Benchmarks will be added
> as I find them necessary to support design decisions.

#### Codebase Atomizer

The *Atomizer* is a tool used to break down the codebase into smaller, more manageable pieces, that can be
retrieved quickly. For example, if you want to use a specific function, say `output_container` to keep things
simple. You can use the *Atomizer* output to retrieve that specific function via a file lookup, `output_container.cpp`.
You can also use any supporting tool you want to pase that file buffer directly inline into your code. Rather than
opening the container header file and copying the specific lines from the file that you need. This will also work
with more complex algorithms that may require an additional data structure to function. For example, if you want to
use Kruskal's algorithm, you can use the *Atomizer* to retrieve the `kruskal.cpp` file which will include the
supporting `DisjointSet` class used within the algorithm. Again resolving you of finding the specific lines of code
within the header file that you need.

#### Full Implementation of the CPH (Competitive Programming Handbook)

The [*Competitive Programming Handbook*]() by Antti Laaksonen is a awesome, all in one, resource for
everything competitive programming. It contains everything from compiling and reading input to sweep line
algorithms including convex hulls. Its an eventual goal of mine to fully implement all the algorithms outlined
in the book. This has the added benefit of an *complete* documentation source of all the algorithms in this
library. This is a long term goal and will likely take a while to complete.

> [!NOTE]
> This is my end game goal for this project. When its completed I will consider this project *done* as so far
> as it will no longer be a major work in progress for me personally. I will still add things here and there
> and work on it when I'm compelled to do so but the core goals of this project will be officially complete.

## License

Copyright (c) Brandon Pacewic

SPDX-License-Identifier: MIT
