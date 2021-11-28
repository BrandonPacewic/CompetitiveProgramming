# python run_cpp.py -i <filename> (without .cpp extension)

import sys, os, getopt

def main(argv):
    cpp_file = ''
    exe_file = ''
    try:
        opts, args = getopt.getopt(argv, "hi:",["help",'ifile='])
    except getopt.GetoptError as err:
        # print help information and exit
        print(err)      
        usage()
        sys.exit(2)
    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-i", "--ifile"):
            cpp_file = a + '.cpp'
            exe_file = a + '.exe'
            run(cpp_file, exe_file)


def usage():
    print('run_cpp.py -i <filename> (without .cpp extension)')

def run(cpp_file, exe_file):
    os.system("echo Compiling " + cpp_file)
    os.system('g++ ' + cpp_file + ' -o ' + exe_file)
    os.system("echo Running " + exe_file)
    os.system("echo -------------------")
    os.system(exe_file)

if __name__=='__main__':
    main(sys.argv[1:])