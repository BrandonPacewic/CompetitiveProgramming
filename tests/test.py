import os

from typing import List

COMPILER = 'g++'
FLAGS = '-Wall -std=c++17'

class Test:
    # Note: fname does not include the .cc extention
    def __init__(self, fname: str, file_dir: str = './') -> None:
        self.fname = fname
        self.file_dir = file_dir

    def compile(self) -> None:
        try:
            os.system(f'{COMPILER} {FLAGS} {self.file_dir}{self.fname}.cc -o {self.fname}.out')
        except:
            print('Compile Error')
            exit(1)
    
    def run(self) -> None:
        try:
            os.system(f'{self.file_dir}{self.fname}.out')
        except:
            print('Test Failed')
            exit(1)


test_directorys = [
    './other/'
]


def create_tests() -> List[Test]:
    tests = []

    for directory in test_directorys:
        for file in os.listdir(directory):
            if file.endswith('.cc'):
                tests.append(Test(file[:-3], directory))

    return tests


def main():
    tests = create_tests()

    for test in tests:
        test.compile()
        test.run()


if __name__ == '__main__':
    main()
