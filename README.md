# Welcome to My LS

---

## Task

The goal of this project is to recreate a simplified version of the Unix `ls` command in C. The program lists files and directories and supports options to modify how they are displayed.

## Description

The program displays the contents of the current directory or lists the contents of a specified directory.

It supports the following options:
* `-a`: Displays hidden files, including files whose names start with a dot.
* `-t`: Sorts entries by modification time, with the most recently modified entries first.
* `-at`: Combines both options.

By default, entries are sorted alphabetically. The program also handles invalid paths and reports errors when necessary.

## Installation

Clone the repository and navigate to the project directory.

Compile the program using the provided Makefile:
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

To clean and recompile the project:
```bash
make re
```

## Usage

Run the program without arguments to list the contents of the current directory:
```bash
./my_ls
```

List the contents of a specific directory:
```bash
./my_ls /path/to/directory
```

Display hidden files:
```bash
./my_ls -a
```

Sort entries by modification time:
```bash
./my_ls -t
```

Combine both options:
```bash
./my_ls -at
```

### The Core Team

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>