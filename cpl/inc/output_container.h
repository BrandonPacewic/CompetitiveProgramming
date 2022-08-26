// output_container library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef OUTPUT_CONTAINER_H_
#define OUTPUT_CONTAINER_H_
#include <core.h>

#include <iostream>

CPL_BEGIN

template <typename T_container>
const void output_container(const T_container& container, const bool& space = true, const bool& new_line = true) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i];

        if (space && i < container.size() - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename T_container>
const void output_reverse_container(const T_container& container, const bool& space = true,
                                    const bool& new_line = true) {
    for (std::size_t i = container.size(); i > 0; --i) {
        std::cout << container[i - 1];

        if (space && i > 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename ForwardIterator>
void output_container(ForwardIterator first, ForwardIterator last, const bool& space = true,
                      const bool& new_line = true) {
    for (; first != last; ++first) {
        std::cout << *first;

        if (space && first != last - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename ForwardIterator>
void output_reverse_container(ForwardIterator first, ForwardIterator last, const bool& space = true,
                              const bool& new_line = true) {
    for (; first != last; ++first) {
        std::cout << *first;

        if (space && first != last - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

CPL_END

#endif  // OUTPUT_CONTAINER_H_
