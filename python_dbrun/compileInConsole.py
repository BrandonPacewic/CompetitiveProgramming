#! /usr/bin/python

# python dbrun -i <filename> (without .cc extension)
import sys, os, getopt


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
    opts, args = getopt.getopt(argv, "hi:",["help",'ifile='])
    for o, a in opts:
        if o in ("-h", "--help"):
            print('run_cpp.py -i <filename> (without .cc extension)')
            sys.exit()
        
        elif o in ("-i", "ifile"):
            cc_file = a + '.cc'
            enterDbgMode(cc_file)
            run(cc_file)
            exitDbgMode(cc_file)


def run(cpp_file):
    os.system("echo Compiling " + cpp_file + " with g++ 17")
    os.system('g++ ' + cpp_file)
    os.system("echo Running " + cpp_file)
    os.system("echo -------------------")
    os.system('./a.out')

if __name__=='__main__':
    main(sys.argv[1:])