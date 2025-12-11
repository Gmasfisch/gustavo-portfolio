# gustavo-portfolio
Projects porfolio

# 👋 Hi, I'm Gustavo — Junior Software Developer (C, Systems Programming)

I'm a Junior Developer based in Berlin, currently studying at **42 Berlin (rank 04)**.  
After working in physiotherapy and hospitality across Europe, I discovered my passion for programming and problem-solving, and committed fully to software development.

I specialize in **C, system-level programming, Linux, concurrency, and core computer science fundamentals**.  
This portfolio highlights the projects that best demonstrate my ability to build reliable, low-level, well-structured software.

---

# 🧰 Tech Stack

### **Languages**
- **C (advanced)**
- Bash / Shell scripting  
- Basic Python  
- Basic JavaScript  

### **Tools & Technologies**
- Linux / POSIX  
- Git & GitHub  
- Makefile  
- Threads & Mutexes (pthread)  
- Process management (`fork`, `execve`, `dup2`)  
- Valgrind / memory debugging  
- Parsing, I/O, and file descriptors  

---

# 🚀 Highlighted Projects

Below is a curated selection of my most relevant projects.  
Full list available on my GitHub profile.

---

## 🔹 **Minishell**
**C, Linux, POSIX APIs, System Programming**

A fully working Bash-like shell supporting command execution, pipes, redirections, environment variables, and built-in commands.

**What I built:**
- `fork`, `execve`, pipes, redirections (`<`, `>`, `>>`)  
- Built-ins: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`  
- Signal handling (`SIGINT`, `SIGQUIT`)  
- Tokenizer + minimal parser with quote handling  
- Robust memory management

Bonus features: minishell

- Logical operators: implemented && (AND) and || (OR) with correct short-circuit evaluation.

- Support for grouped commands using parentheses — (cmd1 && cmd2) || cmd3, including nested evaluation.

- Extended parsing logic for operator precedence and grouped execution contexts.

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/minishell  

---

## 🔹 **Philosophers**
**C, Threads, Concurrency, Synchronization**

A multithreaded simulation of the Dining Philosophers problem, focusing on preventing deadlocks and race conditions.

**What I built:**
- Concurrency model using pthreads  
- Mutex synchronization  
- Deadlock avoidance via fork ordering  
- Monitor thread for death detection  
- Precise timing and safe logging

Bonus features (Process-Based Version): philosophers

Implemented a version where each philosopher runs in its own process, not a thread — requiring full separation of memory spaces.

- Replaced mutex-based synchronization with POSIX semaphores, including:

- Semaphores for forks

- Semaphores for printing/logging

- Semaphores for death monitoring

- Implemented per-process death detection and clean shutdown/signaling for sibling processes.

- Used fork(), waitpid(), and shared semaphores to coordinate state across processes.

- Ensured correct cleanup of semaphores and orphaned processes to avoid resource leaks.

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/philosophers  

---

## 🔹 **libft**
**Custom C standard library**

A complete C library implementing many standard functions for strings, memory, linked lists, and more.

**What I built:**
- Memory manipulation (ft_memcpy, ft_memset…)  
- String functions (ft_split, ft_strjoin…)  
- Linked list utilities  
- Clean APIs and consistent error handling  

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/libft  

---

## 🔹 **get_next_line**
**File I/O, buffers, memory management**

A line-by-line file reader using static buffers and efficient memory control.

**What I built:**
- Reading from file descriptors  
- Static internal state per descriptor  
- Dynamic memory and buffer management

Bonus features: get_next_line

- Support for reading from up to 4096 file descriptors simultaneously (e.g., multiple files, pipes, sockets).

- Per-FD state is stored in a 4096-slot static buffer array, allowing independent line-reading logic for each FD.

- Fully memory-safe: dynamic allocation, cleanup, and buffer rollover handled carefully.

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/get_next_line  

---

## 🔹 **ft_printf**
**Variadic functions, parsing, formatted output**

A full re-implementation of `printf`, supporting conversion specifiers, flags, and formatted output.

**What I built:**
- Variadic argument parsing  
- Conversion handling  
- Modular formatting components  

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/ft_printf  

---

## 🔹 **pipex**
**Pipes, process execution, file descriptors**

A simplified version of shell pipelines.

**What I built:**
- Process creation using `fork`  
- Piping between commands  
- Infile/outfile redirection  
- Error handling for failed commands

Bonus features: pipex

- Support for any number of commands, not just two; fully dynamic pipeline construction (cmd1 | cmd2 | cmd3 | ...).

- Implemented heredoc mode, including delimiter handling and temporary file piping logic.

- Robust error propagation and cleanup when pipelines fail partway.

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/pipex  

---

# 🌍 About 42 Berlin

42 is an international, peer-to-peer, project-based software engineering school with no teachers and no traditional classes.  
Progress is entirely based on completing increasingly complex projects and reviewing the work of others.

I am currently **rank 04**, having completed core system-level projects including Minishell and Philosophers.

---

# 📄 Download CV

You can download my resume here (upload your file after creating the repo):

**➡️ [CV.pdf](./CV.pdf)**

---

# 🇩🇪 Kurzprofil (für deutsche Recruiter)

- Junior Software Developer in Ausbildung bei **42 Berlin (rank 04)**  
- Schwerpunkt: **C, Linux, Systemprogrammierung, Concurrency, Speicherverwaltung**  
- Erfahrung in internationalen und multikulturellen Teams  
- Sprachen: **Spanisch (Muttersprache), Englisch (fließend), Deutsch (B1/B2)**  
- Interesse an Backend, Systemprogrammierung, Embedded oder Low-Level Development  

---

# 📬 Contact

- GitHub: https://github.com/Gmasfisch  
- Email: fischbachgustavo@gmail.com  
- Location: Berlin, Germany  

---

Thank you for visiting my portfolio!  
I'm actively seeking Junior Developer positions and opportunities to grow as a software engineer.

