# python run_cpp.py -i <filename> (without .cpp extension)

import sys, os, getopt

def enterDbgMode(file_name):
    file = open('file_name', 'r')
    lines = file.readlines()
    lines[3] = '#define DBG_MODE'

    file = open('file_name', 'w')
    file.writelines(lines)
    file.close()

def main(argv):
    cpp_file = ''
    try:
        opts, args = getopt.getopt(argv, "hi:",["help",'ifile='])
    except getopt.GetoptError as err:
        # print help information and exit
        print(err)      
        print('run_cpp.py -i <filename> (without .cpp extension)')
        sys.exit(2)
    for o, a in opts:
        if o in ("-h", "--help"):
            print('run_cpp.py -i <filename> (without .cpp extension)')
            sys.exit()
        elif o in ("-i", "--ifile"):
            cpp_file = a + '.cc'
            enterDbgMode(cpp_file)
            run(cpp_file)


def run(cpp_file):
    os.system("echo Compiling " + cpp_file + " with g++ 17")
    os.system('g++ ' + cpp_file)
    os.system("echo Running " + cpp_file)
    os.system("echo -------------------")
    os.system('./a.out')

if __name__=='__main__':
    main(sys.argv[1:])