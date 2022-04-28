import os
import subprocess

from typing import List

COMPILER = 'g++'
FLAGS = '-Wall -std=c++17'

class Test:
    # Note: fname does not include the .cc extention
    def __init__(self, fname: str, file_dir: str = './') -> None:
        self.fname = fname
        self.file_dir = file_dir

    def compile(self) -> bool:
        os.chdir(self.file_dir)

        try:
            os.system(f'{COMPILER} {FLAGS} {self.fname}.cc -o {self.fname}.out')
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

            os.system(f'{self.file_dir}{self.fname}.out')
        except:
            print('Test Failed')
            return False
        
        return not exit_code


def create_tests() -> List[Test]:
    os.chdir('./tests/')

    tests = []

    for root, _, files in os.walk('./'):
        for file in files:
            if file.endswith('.test.cc'):
                tests.append(Test(file[:-3], f'{root}/'))
                print(f'Found file {file}')

    return tests


def test_scripts() -> int:
    tests = create_tests()
    sucess = True

    for test in tests:
        sucess = sucess and test.compile() and test.run()

    print(sucess)

    if sucess:
        return 0
    else:
        return 1