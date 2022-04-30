import os

def main():
    for dirpath, _, filenames in os.walk('src/'):
        for filename in filenames:
            if filename.endswith('.cc'):
                os.system(f'clang-format -i -style=file {dirpath}/{filename}')


if __name__ == '__main__':
    main()