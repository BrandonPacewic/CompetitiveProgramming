import os

def main():
    for dirpath, _, filenames in os.walk('./'):
        for filename in filenames:
            if filename.endswith('.cc') or filename.endswith('.hpp'):
                print(f'Found file {dirpath}/{filename}')
                os.system(f'clang-format -i -style=file {dirpath}/{filename}')


if __name__ == '__main__':
    main()