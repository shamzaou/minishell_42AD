
# Minishell


## Introduction

Minishell is a simple Unix shell implementation written in C. It provides a command-line interface to interact with the operating system, allowing users to execute commands, manage processes, and manipulate files. The project aims to deepen understanding of system calls, process management, and command-line parsing.

## Features

- **Command Execution**: Execute external commands by forking and calling `execve()`.
- **Built-in Commands**: Support for built-in commands such as `cd`, `echo`, `pwd`, `export`, `unset`, and `env`.
- **Input/Output Redirection**: Handle input/output redirection (`<`, `>`, `>>`) and piping (`|`) between commands.
- **Environment Variables**: Manage environment variables, including setting, getting, and removing them.
- **Signal Handling**: Handle signals such as `Ctrl+C` (SIGINT) and `Ctrl+\` (SIGQUIT) gracefully.
- **Error Handling**: Provide informative error messages for invalid commands, syntax errors, and exceptional conditions.

## Project Structure

The Minishell project typically consists of the following components:

.<br>
├── Env : Environment-related files.<br>
├── Libft : Library containing utility functions (if used).<br>
├── Parsing : Files related to command-line parsing.<br>
├── Signals : Signal handling related files.<br>
├── Makefile : Makefile for building the project.<br>
├── main.c  Main source file containing the entry point of the program.<br>
├── README.md : Project documentation.<br>
└── minishell.h : Header file containing function prototypes and constant definitions.<br>

## Installation

To build Minishell, follow these steps:

1. Clone the repository:

   ```bash
   git clone <repository_url>
   ```

2. Navigate to the project directory:

   ```bash
   cd minishell
   ```

3. Compile the program using the provided Makefile:

   ```bash
   make
   ```

## Usage

To run Minishell, execute the following command:

```bash
./minishell
```

This will start the Minishell prompt, where you can enter commands and interact with the shell. Use built-in commands or external commands as needed.

Example:

```bash
$ ./minishell
minishell> ls -l
total 72
-rw-r--r-- 1 user user   432 Jan  1 10:00 README.md
-rwxr-xr-x 1 user user 48576 Jan  1 10:00 minishell
...
minishell> exit
$
```

## Contributing

Contributions to the Minishell project are welcome! If you have any ideas, enhancements, or bug fixes, feel free to open an issue or submit a pull request.
