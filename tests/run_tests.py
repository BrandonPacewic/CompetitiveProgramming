# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

import os
import sys

BUILD_OUTPUT_DIR = 'out\\build'
TEST_OUTPUT_DIR = 'tests\\cpl'

def main() -> None:
    if len(sys.argv) != 2:
        cmake_source_dir = './'
    else:
        cmake_source_dir = sys.argv[1]

    if not sys.platform.startswith('win32'):
        print('This script is only supported on Windows')
        sys.exit(1)

    print('Running tests...')
    os.chdir(f'{cmake_source_dir}\\{BUILD_OUTPUT_DIR}')

    # For each build config (e.g. x64-Debug, x64-Release, etc.)
    # run the '.exe's in the 'tests\\cpl' directory
    for build_config in os.listdir():
        os.chdir(build_config)

        for test in os.listdir(TEST_OUTPUT_DIR):
            test_path = f'{TEST_OUTPUT_DIR}\\{test}'
            if not os.path.isfile(test_path):
                continue
        
            if test.split('.')[-1] != 'exe':
                continue

            print(f'Running {test}...')
            result = os.system(test_path)
            if result != 0:
                print(f'{test} failed with exit code {result}')
                sys.exit(1)

    print('All tests passed')


if __name__ == '__main__':
    main()
