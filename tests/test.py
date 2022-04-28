import os

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
            os.system(f'{self.file_dir}{self.fname}.out')
        except:
            print('Test Failed')
            return False
        
        return True


def create_tests() -> List[Test]:
    tests = []

    for root, _, files in os.walk('./'):
        for file in files:
            if file.endswith('.test.cc'):
                tests.append(Test(file[:-3], f'{root}/'))
                print(f'Found file {file}')

    return tests


def test_scripts() -> bool:
    tests = create_tests()
    sucess = True

    for test in tests:
        sucess = sucess and test.compile() and test.run()

    return sucess