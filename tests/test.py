# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

import os
import sys

def main(cmake_source_dir: str) -> None:
    print("the test ran")
    print(cmake_source_dir)


if __name__ == '__main__':
    main(sys.argv[1])