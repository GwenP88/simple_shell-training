# Simple Shell

## Description

**Simple Shell** is a basic UNIX command-line interpreter written in C as part of the Holberton School curriculum.  
It reproduces essential behaviors of the UNIX shell by executing commands found in the `PATH`, handling built-in commands, and supporting both interactive and non-interactive modes.

This project focuses on:
- Process creation and management
- Environment variables
- Command parsing
- System calls (`fork`, `execve`, `wait`)
- Understanding how a shell works internally

---

## Features

- Interactive mode with custom prompt
- Non-interactive mode (commands from standard input)
- Execution of commands using the `PATH`
- Built-in commands:
  - `exit` – exits the shell
  - `env` – prints the environment
- Custom implementation of `_getenv`
- Proper error handling and exit status
- Fully compliant with **Betty** style
- No memory leaks

---

## Requirements

- Allowed editors: `vi`, `vim`, `emacs`
- OS: **Ubuntu 20.04 LTS**
- Compiler: `gcc`
- Compilation flags:
  ```bash
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
  ```
- All files end with a new line
- No memory leaks
- Betty style checked with `betty-style.pl` and `betty-doc.pl`

---

## Installation

Clone the repository:

```bash
git clone https://github.com/YOUR_USERNAME/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```

Compile the program:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Usage

### Interactive Mode

```bash
./hsh
```

### Non-Interactive Mode

```bash
echo "ls" | ./hsh
```

---

## Built-in Commands

| Command | Description                    |
|---------|--------------------------------|
| `exit`  | Exit the shell                 |
| `env`   | Print the current environment  |
| `cd`    | Declared but not implemented   |

---
## Manual Page

This project includes a manual page describing the usage and behavior of the shell.
The man page file is located at:

`man_1_simple_shell`


To display it, run:

`man ./man_1_simple_shell`

---

## Examples / Tests

### Interactive mode (local run)

```bash
./hsh
```

Example session:

```
-_- \_(ツ)_/ $ ls
AUTHORS  README.md  builtins.c  builtins_handler.c  getenv.c  hsh  man_1_simple_shell  parser.c  path.c  shell.h  simple_shell.c
-_- \_(ツ)_/ $ bin/ls
./hsh: 2: bin/ls: not found
-_- \_(ツ)_/ $ /bin/ls
AUTHORS  README.md  builtins.c  builtins_handler.c  getenv.c  hsh  man_1_simple_shell  parser.c  path.c  shell.h  simple_shell.c
-_- \_(ツ)_/ $ pwd
/home/gpichot/holbertonschool-simple_shell
-_- \_(ツ)_/ $ env
SHELL=/bin/bash
COLORTERM=truecolor
VSCODE_DEBUGPY_ADAPTER_ENDPOINTS=/home/gpichot/.vscode-server/extensions/ms-python.debugpy-2025.18.0-linux-x64/.noConfigDebugAdapterEndpoints/endpoint-dc6b887d58150219.txt
...
-_- \_(ツ)_/ $ exit
```

### Non-interactive mode (local run)

Command found using PATH:

```bash
echo "ls" | ./hsh
```

Output:

```
AUTHORS  README.md  builtins.c  builtins_handler.c  getenv.c  hsh  man_1_simple_shell  parser.c  path.c  shell.h  simple_shell.c
```

Command executed with absolute path:

```bash
echo "/bin/ls" | ./hsh
```

Output:

```
AUTHORS  README.md  builtins.c  builtins_handler.c  getenv.c  hsh  man_1_simple_shell  parser.c  path.c  shell.h  simple_shell.c
```

Relative path not found:

```bash
echo "bin/ls" | ./hsh
```

Output:

```
./hsh: 1: bin/ls: not found
```

Command not found and exit status:

```bash
echo "doesnotexist" | ./hsh
echo $?
```

Output:

```
./hsh: 1: doesnotexist: not found
127
```

---

## Expected Behavior

- The prompt is displayed only in interactive mode.
- Commands are executed if found in PATH or provided as absolute paths.
- If a command is not found, an error message is printed to stderr.
- The shell returns exit status 127 for unknown commands.
- The shell exits cleanly when exit is called.

---

## Error Handling

The shell handles errors in a behavior similar to standard UNIX shells:

- If a command is not found in `PATH` and is not an absolute path, an error message is printed to `stderr`.
- If `execve` fails, the shell prints an error message and continues execution.
- The shell returns exit status `127` when a command is not found.
- The shell does not crash on invalid input (empty line, spaces only).
- The shell exits cleanly when `exit` is called.

All errors are handled without memory leaks.

---

## Files Description

| File                  | Description                              |
|-----------------------|------------------------------------------|
| `shell.h`             | Header file with macros, structures, and prototypes |
| `simple_shell.c`      | Main loop and shell logic                |
| `parser.c`            | Input parsing and tokenization           |
| `path.c`              | PATH parsing and command lookup          |
| `getenv.c`            | Custom _getenv implementation            |
| `builtins.c`          | Built-in commands                        |
| `builtins_handler.c`  | Built-in detection and execution         |
| `AUTHORS`             | List of contributors                     |
| `README.md`           | Project documentation                    |
| `man_1_simple_shell`  | Manual page for the shell                |

---

## Future Improvements

We are planning to continue developing this shell with the implementation of the cd command. Currently declared but not yet functional, we plan to fully implement this built-in command to allow directory navigation.

This enhancement will make our shell more complete and functional for basic navigation tasks.

---

## Authors

**Gwenaëlle Pichot**  
GitHub: [https://github.com/GwenP88](https://github.com/GwenP88)

**Hugo U.**  
GitHub: [https://github.com/hugou74130/holbertonschool-simple_shell](https://github.com/hugou74130/holbertonschool-simple_shell)

---

## Acknowledgements

- Holberton School
- Linux manual pages
- GNU documentation

---

## License

This project is for educational purposes only as part of the Holberton School curriculum.
