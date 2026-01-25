*This project has been created as part of the 42 curriculum by thde-sou and tide-pau.*

# Minishell

## Description
Minishell is a simplified implementation of a Unix shell, inspired by Bash.
The goal of this project is to understand how shells work internally, including
process creation, signal handling, pipes, redirections, and environment variables.

This shell provides an interactive prompt, executes commands found in the PATH
or via relative and absolute paths, and implements a set of required built-in commands.

## Instructions
Navigate to the Minishell directory and then run the following command to compile the project "make" to compile the shell,
after that you will need to write "./minishell" to start the shell.

### Compilations
```bash
make
./minishell
```
## Resources

### GNU Bash Manual
- https://www.gnu.org/software/bash/manual/

### Man Pages
- man bash
- man execve
- man fork
- man pipe
- man dup
- man dup2
- man waitpid
- man signal
- man readline
- man sigaction
- man sigemptyset
- man getcwd
- man perror
- man stat
- man access

### AI Utilization

AI tools were used as a support to acquire information and to understand system calls, the shell behaviour.

AI was mainly used to clarify documentation, explore different approaches and validate understanding.

All implementations and decisions were made by the authors, and the code was fully written and understood by them.