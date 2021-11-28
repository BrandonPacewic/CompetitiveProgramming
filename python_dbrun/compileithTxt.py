#! /usr/local/bin/python

# python dbrunf -i <filename> (without .cc extension)
import sys, os, getopt

def getOutput():
    file = open('ou.txt', 'r')
    return file.readlines()

def getExpected():
    file = open('ex.txt', 'r')
    return file.readlines()

def compairExpectedVsOutput():
    print('Compairing...')
    output = getOutput()
    expected = getExpected()

    print('-----------\nExpected:\n')
    for i in expected:
        print(i[:len(i) - 1])

    print('\n----------\nOutput:\n')
    for i in output:
        print(i[:len(i) - 1])

    print('\n----------')

    countGood = 0
    for i in range(len(output)):
        if (output[i] == expected[i]):
            countGood += 1
    
    print('\n' + str(countGood) + ' / ' + str(len(output)) + ' Tests Passed\n')

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

def enterTxtMode(file_name):
    file = open(file_name, 'r')
    lines = file.readlines()
    lines[2] = '#define TEXT_IO' + '\n'

    file = open(file_name, 'w')
    file.writelines(lines)
    file.close()

def exitTxtMode(file_name):
    file = open(file_name, 'r')
    lines = file.readlines()
    lines[2] = '\n'

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
            enterTxtMode(cc_file)
            run(cc_file)
            exitDbgMode(cc_file)
            exitTxtMode(cc_file)
            compairExpectedVsOutput()


def run(cpp_file):
    os.system("echo Compiling " + cpp_file + " with g++ 17")
    os.system('g++ ' + cpp_file)
    os.system("echo Running " + cpp_file)
    os.system("echo -------------------")
    os.system('./a.out')

if __name__=='__main__':
    main(sys.argv[1:])