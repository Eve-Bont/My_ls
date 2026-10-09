# Welcome to My LS

---

## Task

The goal of this project is to recreate a simplified version of the Unix `ls` command in C.
The program lists files and directories, allowing users to inspect directory contents and sort entries alphabetically or by modification date.

## Description

This project implements a custom version of the `ls` command.
The program accepts files, directories and command-line options as arguments. It uses system calls and directory-handling functions to retrieve file information and display directory contents.

The following options are supported:
* `-a`: display hidden files, including entries whose names begin with a dot (`.`).
* `-t`: sort entries by modification date, with the most recently modified entries first.
* `-at`: combine both options to display hidden files and sort entries by modification date.

By default, entries are sorted alphabetically.
The program can display the contents of the current directory when no file or directory is specified. It can also display individual files or the contents of specified directories.
Invalid file and directory paths produce an error message.

## Installation

Compile the project using the provided Makefile:
```bash
make
```

To remove the generated object files:
```bash
make clean
```

To remove all generated files, including the executable:
```bash
make fclean
```

To rebuild the project from scratch:
```bash
make re
```

## Usage

Display the contents of the current directory:
```bash
./my_ls
```

Display the contents of a specific directory:
```bash
./my_ls my_directory
```

Display a specific file:
```bash
./my_ls my_file.txt
```

Display all entries, including hidden files:
```bash
./my_ls -a
```

Sort entries by modification date, with the most recent first:
```bash
./my_ls -t
```

Combine both options:
```bash
./my_ls -at
```

You can also specify multiple files and directories:
```bash
./my_ls file1.txt my_directory file2.txt
```

### The Core Team

Made at Qwasar SV -- Software Engineering School