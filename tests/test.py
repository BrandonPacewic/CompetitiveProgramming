# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

import mimetypes
import os
import sys


TEST_OUTPUT_DIR = 'build/tests/cpl'


def main(cmake_source_dir: str) -> None:
    os.chdir(f'{cmake_source_dir}/{TEST_OUTPUT_DIR}')

    if sys.platform.startswith('linux'):    
        for file in os.listdir('.'):
            if not file.endswith('.a'):
                continue

            if file.split('.')[2] == 'run':
                print(f'Running test {file}')
                result = os.system(f'./{file}')

            if result != 0:
                print(f'Test {file} failed')
                sys.exit(1)
    elif sys.platform.startswith('win32'):
        for file in os.listdir('.'):
            if not file.endswith('.exe'):
                continue

            if file.split('.')[2] == 'run':
                print(f'Running test {file}')
                result = os.system(f'{file}')

            if result != 0:
                print(f'Test {file} failed')
                sys.exit(1)

    print('All tests passed')


if __name__ == '__main__':
    main(sys.argv[1])
