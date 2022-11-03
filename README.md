# C++ Competitive Programming Library

![Clang Format Check](https://github.com/BrandonPacewic/CompetitiveProgramming/actions/workflows/clang-format-check.yml/badge.svg?event=push)

Competitive programming is a passion of mine I and would love to share it with anyone and everyone. It is my intention
to maintain this library and to make it as easy as possible for anyone to use it as they wish.

## Goals

I wish that I could do everything but I can't. Here are the current goals I have for this project as of 10/3/2022.

- Static Library structure that functions in both a CMake project environment and allows for code snippets to be
removed from the project and be used in a standalone environment.
- Test coverage for all algorithms and containers.
- Azure Pipelines CI/CD for automated building and testing.
- Future C++ standards support.

## Non-Goals

As I briefly mentioned above, I am only one person and as such cannot do everything. To that end I have things that I
will not be doing in respect to this project.

- Compatibility with other platforms.
- Full code documentation.
- Support for previous C++ standards.

In respect to compatibility with other platforms, I will not be supporting the library on any platform other than Windows.
I currently (and plan to) use the MSVC compiler for the library itself. For more information see the getting started section.
However this does not mean that you cannot use code snippets on other platforms. As I mention above, the Library is designed
in such a way that allows for the removal of select algorithms and containers to be used in a standalone environment. As
long as your compiler supports the latest version of C++ you should be fine on other platforms.

## Library Languages

If you where to pick any language to use for competitive programming it would
definitely be C++. Mainly in terms of efficiency and the capabilities of the
Standard Library. For these reasons all of the source code is written in C++.

## Starting Competitive Programming

If your not sure where to start I recommend HackerRank, Codewars, LeetCode, and
CodeForces to start. The bigger competitions such as Google Code Jam and
Facebook Hacker Cup are also fantastic but they have a slightly higher
barrier of entry.

If you are looking for a book to read checkout the
[Competitive Programmer’s Handbook](https://cses.fi/book/book.pdf) by Antti Laaksonen.

If you are looking for people to watch I recommend the following people:

- [Errichto](https://www.youtube.com/c/Errichto)
- [Neal Wu](https://www.youtube.com/c/NealWuProgramming)
- [William Lin](https://www.youtube.com/c/WilliamLin168)

## How to consume

You will need a copy of the source code saved locally in order to use it. Simply create a clone of the repository and
put it in a easy to access location. Then just copy and paste code whenever you need it.

This is an unfortunate side effect of how competitive programming contests work. All of your code outside what the
compiler includes must be submitted with your solution, all in one file. For this reason the code in this library is
build in a way that allows it to work and be compiled separately from the library itself.

## Getting Started

It is my personal preference to use the Visual Studio IDE for compiling the library and testing. However, there are
many ways of going about this as long as you have the correct knowledge.

### How to Build with the Visual Studio IDE

1. Install the latest version of the Visual Studio IDE.
    - Select the C++ development workload.
    - I recommend selecting "C++ CMake tools for Windows" in the VS Installer as this will simplify the process of getting
CMake and Ninja working.
    - Otherwise, install CMake 3.23 or later and the latest version of Ninja.
    - I also recommend selecting "Python 3 64-bit" in the VS Installer as well.
    - Otherwise, insure that Python 3.9 or later is available to CMake.
2. Open Visual Studio and choose the "Clone or checkout code" option. Enter the URL of this repository,
`https://github.com/BrandonPacewic/CompetitiveProgramming`.
3. Open a terminal in the IDE (``Ctrl + ` `` by default) or press "View" and then "Terminal" in the menu bar.
4. Invoke `git submodule update --init --progress` in the terminal.
5. Thats it! Everything you need to build the project is available to you inside of `CMakeSettings.json`.

## Checkout my profiles

- [Code Forces](https://codeforces.com/profile/BrandonPacewic)
- [Code Wars](https://www.codewars.com/users/BrandonPacewic)

## License

Copyright (c) Brandon Pacewic

SPDX-License-Identifier: MIT
