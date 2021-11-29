#! /usr/bin/python

# usage run <filename> (without .cc extention)

import sys, os

def run(cc_file):
    os.system("echo Compiling " + cc_file + "with C++17")
    os.system("g++ " + cc_file)
    os.system("echo Running " + cc_file)
    os.system("echo -----")
    os.system("./a.out")


def main(argv):
    cc_file = argv[0] + '.cc'
    run(cc_file)


if __name__ == '__main__':
    main(sys.argv[1:])