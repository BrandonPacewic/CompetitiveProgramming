#! /usr/bin/python

# python dbrun <filename> (without .cc extension)
import sys, os


def enterDbgMode(file_name):
    file = open(file_name, 'r')
    lines = file.readlines()
    lines[3] = '#define DBG_MODE' + '\n'

    file = open(file_name, 'w')
    file.writelines(lines)
    file.close()


def exitDbgMode(file_name):
    file = open(file_name, 'r')
    lines = file.readlines()
    lines[3] = '//dbg' + '\n'

    file = open(file_name, 'w')
    file.writelines(lines)
    file.close()


def main(argv):
    cc_file = argv[0] + '.cc'
    enterDbgMode(cc_file)
    run(cc_file)
    exitDbgMode(cc_file)


def run(cpp_file):
    os.system("echo [DEBUG MODE] Compiling " + cpp_file + " with C++17")
    os.system('g++ ' + cpp_file)
    os.system("echo Running " + cpp_file)
    os.system("echo ----------")
    os.system('./a.out')


if __name__ == '__main__':
    main(sys.argv[1:])
