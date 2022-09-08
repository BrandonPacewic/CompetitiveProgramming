# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

import mimetypes
import os
import sys


TEST_OUTPUT_DIR = 'build/tests/cpl'


def main(cmake_source_dir: str) -> None:
    os.chdir(f'{cmake_source_dir}/{TEST_OUTPUT_DIR}')

    do_run = lambda x: x.split('.')[2] == 'run'

    for file in os.listdir('.'):
        if not file.endswith('.a'):
            continue

        if do_run(file):
            print(f'Running test {file}')
            result = os.system(f'./{file}')

        if result != 0:
            print(f'Test {file} failed')
            sys.exit(1)

    print('All tests passed')


if __name__ == '__main__':
    main(sys.argv[1])