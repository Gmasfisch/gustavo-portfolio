# Pipex

A simplified Unix pipeline implementation in C as part of the 42 Berlin curriculum.  

---

## Overview

pipex recreates the behavior of shell pipelines, allowing the output of one command to be passed as the input to another.  
This project helped me master:  

- Process creation and management
- Pipes and file descriptor redirection
- Command execution with fork() and execve()
- Error handling and memory management

**Course:** 42 Berlin — 2025 (Rank 02)  

---

## Key Features — Mandatory

- Execute multiple commands connected by pipes (|)
- Input and output file redirection (< and >)
- Built-in error handling for invalid commands and files
- Works with any number of commands (bonus)
- Supports heredoc mode (bonus)

---

## Key Features — Bonus  

- Unlimited pipeline support  
  - Commands can be chained arbitrarily  
  - Proper handling of intermediate pipes and processes  
- Heredoc mode  
  - Accepts input directly from the terminal until a delimiter line is reached  
  - Redirects this input into the first command in the pipeline  

---

## Architecture & Design

- Parent process: orchestrates pipeline creation and command execution
- Child processes: each executes a single command with proper input/output redirection
- Pipes: dynamically allocated depending on the number of commands
- Heredoc handling: reads input until a delimiter, passes to the first child via pipe
- Memory management: ensures all dynamically allocated resources are freed after execution

## Installation & Build

## Mandatory version

```bash
# Clone repo
git clone https://github.com/Gmasfisch/gustavo-portfolio.git
cd gustavo-portfolio/pipex
make

./pipex file1 cmd1 | cmd2 file2

Equivalent shell command: < file1 cmd1 | cmd2 > file2

# Example
./pipex input.txt seq 1 10 | shuf output.txt
```

### Bonus version
```bash  
make bonus 
 
./pipex_bonus infile cmd1 cmd2 cmd3 outfile

Equivalent shell command: < infile cmd1 | cmd2 | cmd3 > outfile

# Example
./pipex_bonus input.txt seq 1 10 | head -n 5 | shuf output.txt
```
## Learning Outcomes

- Concurrency using threads and processes

- Synchronization with mutexes vs semaphores

- Timing precision with microsecond granularity

- Avoiding deadlocks and starvation

- Process control using fork(), sem_open(), waitpid()

## Author / Contact

Gustavo Fischbach — 42 Berlin (rank 04)  
**GitHub Portfolio:** [Portfolio](https://github.com/Gmasfisch/gustavo-portfolio)  
**GitHub Profile:** [Profile](https://github.com/Gmasfisch)  
**Email:** fischbachgustavo@gmail.com