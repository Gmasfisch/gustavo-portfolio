# Minishell

A minimal UNIX shell implemented as part of the 42 Berlin curriculum.

---

## Overview

Minishell is a compact, POSIX-compatible shell implemented in C. It supports executing commands, pipes, redirections, environment variables, and built-in commands.  
This project helped me master process creation, command parsing, memory management, and signal handling.  

**Course:** 42 Berlin — 2024 (Rank 04)

---

## Key Features

- Execute external commands using `fork()` and `execve()`.  
- Pipes (`|`) and multiple piped commands.  
- Redirections: input `<`, output `>`, append `>>`.  
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`.  
- Signal handling: `SIGINT` and `SIGQUIT`.  
- Quote handling (single and double).  
- Environment variable expansion.  

### Bonus Features

- Logical operators: `&&` (AND) and `||` (OR) with short-circuit evaluation.  
- Grouping commands using parentheses `()` including nested groups.  
- Wildcard `*` support for filename expansion in commands.  

---

## Architecture & Design

- **Tokenizer:** Breaks input into commands, operators, and arguments while handling quotes and escaped characters.  
- **Parser:** Builds a structure for execution that respects logical operators, grouping, and command precedence.  
- **Executor:** Handles built-ins vs external commands, pipes, and redirections.  
- **Memory Management:** Careful use of `malloc`/`free` to avoid leaks.  
- **Signals:** Parent and child processes handle signals properly to avoid termination issues.  

**Design choices:**  
- Modular architecture separating parsing, execution, and utilities.  
- Custom wildcard expansion to replicate basic shell globbing behavior.  
- Logical operator evaluation respects short-circuit rules and nesting.  

---

## Installation / Build

Tested on Linux (Ubuntu recommended):

```bash
# Clone repo
git clone https://github.com/Gmasfisch/gustavo-portfolio.git
cd gustavo-portfolio/minishell

# Build the shell
make

Usage

# Start the shell:

./minishell


# Example commands inside the shell:

$ echo "Hello World"
$ ls -la | grep src > out.txt
$ cat < out.txt
$ export VAR=42; echo $VAR
$ cd ..
$ mkdir test && cd test || echo "Failed"
$ echo *.c
$ (echo hi && echo bye) || echo fail
```

## Challenges & Solutions

- Parsing logical operators and parentheses: Implemented recursive parsing to handle grouping and operator precedence.
- Wildcard expansion: Built a custom globbing solution to expand `*` in arguments safely.
- Signal handling: Ensured that `SIGINT` and `SIGQUIT` do not terminate the parent shell unexpectedly.
- Memory leaks: Used Valgrind to track allocations and prevent memory leaks.

## Learning Outcomes

- Advanced C programming: process creation, memory management, and parsing.
- Developed understanding of shell command evaluation, logical operators, and globbing.
- Hands-on experience with modular design and signal-safe execution.
- Improved debugging and problem-solving skills under constraints.

Project Status

✅ Completed (includes all mandatory and bonus requirements).

Author / Contact

Gustavo Fischbach — 42 Berlin (rank 04)  
**GitHub Portfolio:** [Portfolio](https://github.com/Gmasfisch/gustavo-portfolio)  
**GitHub Profile:** [Profile](https://github.com/Gmasfisch)
**Email:** fischbachgustavo@gmail.com