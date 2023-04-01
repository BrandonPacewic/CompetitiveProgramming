# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

import os
import sys

FILES_DIRS = ["cpl/inc", "cpl/src", "tests/cpl"]
FILE_TARGETS = (".cpp", ".h", ".hpp")
FORMAT_COMMAND = "clang-format -i -style=file"

def main():
    if not os.path.exists(os.path.join(os.getcwd(), ".clang-format")):
        while True: 
            os.chdir("../")
            if os.path.exists(os.path.join(os.getcwd(), ".clang-format")):
                print(f"Found root of project at {os.getcwd()}")
                break

    files = []
    for file_dir in FILES_DIRS:
        for root, dirs, file_names in os.walk(file_dir):
            for file_name in file_names:
                if file_name.endswith(FILE_TARGETS):
                    files.append(os.path.join(root, file_name))

    for file in files:
        previous_file_state = open(file, "r").read()
        os.system(f"{FORMAT_COMMAND} {file}")
        new_file_state = open(file, "r").read()

        if previous_file_state != new_file_state:
            print(f"File {file} is not formatted correctly!")
            sys.exit(1)

    print("All files formatted correctly")


if __name__ == "__main__":
    main()
