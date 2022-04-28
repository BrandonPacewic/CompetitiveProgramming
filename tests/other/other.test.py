import os

def main():
    compiler = 'g++'
    flags = '-std=c++17 -Wall -O2 -DONLINE_JUDGE'
    input = 'encoding.test.cc'
    output = 'encoding.test.out'

    try:
        os.system(f'{compiler} {flags} {input} -o {output}')
    except:
        print('Compile Error')
        exit(1)

    try:
        os.system(f'./{output}')
    except:
        print('Tests Failed')
        exit(1)


if __name__ == '__main__':
    main()