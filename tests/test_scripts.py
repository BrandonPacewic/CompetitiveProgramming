# MIT License
#
# Copyright (c) 2022 Brandon Pacewic
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import subprocess

from typing import List

COMPILER = 'g++'
FLAGS = '-Wall -std=c++17'

class Test:
    # Note: fname does not include the .cpp extension
    def __init__(self, fname: str, file_dir: str = './') -> None:
        self.fname = fname
        self.file_dir = file_dir

    def compile(self) -> bool:
        os.chdir(self.file_dir)

        try:
            os.system(f'{COMPILER} {FLAGS} {self.fname}.cpp -o {self.fname}.out')
        except:
            print('Compile Error')
            return False

        os.chdir('../') 
        return True

    def run(self) -> bool:
        try:
            process = subprocess.Popen(
                f'{self.file_dir}{self.fname}.out', 
                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            process.communicate()
            exit_code = process.wait()

        except:
            print('Execute Failed')
            return False

        return not exit_code


def create_tests() -> List[Test]:
    os.chdir('./tests/')

    tests = []

    for root, _, files in os.walk('./'):
        for file in files:
            if file.endswith('.test.cpp'):
                tests.append(Test(file[:-4], f'{root}/'))
                print(f'Found file {file}')

    return tests


def test_scripts() -> int:
    tests = create_tests()
    success = True

    for test in tests:
        current_test = test.compile() and test.run()
        success = success and current_test

        if current_test:
            print(f'Test {test.fname.split(".")[0]} passed')
        else:
            print(f'Test {test.fname.split(".")[0]} failed')

    return 0 if success else 1