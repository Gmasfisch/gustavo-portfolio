# gustavo-portfolio

Projects portfolio

# 👋 Hi, I'm Gustavo — SAP ABAP Developer | C & Systems Programming

I'm a developer based in Berlin, **SAP Certified as a Back-End Developer (ABAP Cloud)** and
**Integration Developer**, currently studying at **42 Berlin (rank 06)**.

After working in physiotherapy and hospitality across Europe, I discovered my passion for
programming and problem-solving, and committed fully to software development.

My focus is **SAP ABAP Cloud** — RAP business objects, CDS views, and clean-core extensions —
built on a foundation of **C, C++, system-level programming, Linux, and concurrency** from 42 Berlin.
That combination means I came to ABAP already understanding memory, processes, and how
software actually runs underneath the abstraction.

---

### 🎓 Certifications

🎓 **[SAP Certified – Back-End Developer, ABAP Cloud](https://www.credly.com/badges/c8bb9647-35c5-4531-a472-e07d758b70d6/public_url)** · July 2026

🎓 **SAP Certified – Integration Developer** · September 2026

# 🧰 Tech Stack

### **SAP / ABAP**

- ABAP Cloud (SAP Certified)
- RAP — RESTful Application Programming Model (behavior definitions, determinations, validations, EML)
- CDS view entities, associations, and access control (DCL)
- ABAP SQL — joins, subqueries, aggregates
- Object-oriented ABAP, inheritance, exception classes (T100)
- ABAP Dictionary — domains, data elements, structures, table types
- Eclipse / ABAP Development Tools (ADT)
- SAP Integration Suite (SAP Certified Integration Developer)

### **Languages**

- **C (advanced)**
- **C++ (C++98)**
- Bash / Shell scripting
- Basic Python
- Basic JavaScript

### **Tools & Technologies**

- Linux / POSIX
- Git & GitHub
- Makefile
- Docker & Docker Compose
- NGINX, MariaDB, WordPress (wp-cli), TLS/SSL (OpenSSL)
- Network programming — sockets, non-blocking I/O, `poll()`, HTTP/1.1, CGI
- Threads & Mutexes (pthread)
- Process management (`fork`, `execve`, `dup2`)
- Valgrind / memory debugging
- Parsing, I/O, and file descriptors

---

# 🚀 Highlighted Projects

Below is a curated selection of my most relevant projects.  
Full list available on my GitHub profile.

---

## 🔹 **Webserver**

**C++98, Network Programming, HTTP/1.1, CGI** · *Team project (2 people)*

An HTTP/1.1 web server written in C++98 with no external libraries, driven by a single non-blocking `poll()` event loop. Configurable through an NGINX-style configuration file.

**What I built (my part):**

- The core event loop: listening sockets, `accept`, and per-client connections, all non-blocking and handled through one `poll()`
- Connection state and read/write buffers, including partial sends (`POLLOUT`) so large responses never block the server
- HTTP request parsing: request line, headers, query string, `Content-Length` and chunked bodies
- Response generation: static files, status codes, custom error pages, redirections, autoindex
- Timeouts for idle clients and clean shutdown on `SIGINT` / `SIGTERM`

**What my teammate built:**

- The configuration file parser (tokenizer, `server` / `location` blocks, directives)
- The CGI implementation (`fork` / `execve`, environment variables, pipes)

**Built together:** wiring the CGI pipes into the same `poll()` loop, so a slow script never blocks other clients.

**Features:**

- Multiple servers and ports, with longest-prefix `location` matching
- `GET`, `POST` and `DELETE`
- File upload (`multipart/form-data`) and per-location `client_max_body_size` (`413` when exceeded)
- Configurable error pages and HTTP redirections
- CGI with configurable interpreters per extension (`cgi_ext`); tested with Python and shell scripts
- CGI timeout (`504`) with the child process killed and reaped
- Stress-tested with `siege` (25 concurrent clients, 100% availability) and with the 42 tester (20 workers, each sending 5 requests of 100 MB); also checked for leaks and file descriptor inheritance

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/webserver

---

## 🔹 **Inception**

**Docker, Docker Compose, NGINX, WordPress, MariaDB, System Administration**

A small web infrastructure built entirely with Docker inside a Debian virtual machine, using only self-written images (mandatory part).

**What I built:**

- Three containers, each from its own Dockerfile on Debian `bookworm`: **NGINX**, **WordPress + php-fpm**, **MariaDB**
- NGINX as the single entrypoint: port 443 only, TLSv1.2 / TLSv1.3 with a self-signed certificate, PHP forwarded to WordPress over FastCGI
- Automatic WordPress installation with `wp-cli` at container startup, and database/user creation for MariaDB
- Idempotent entrypoint scripts (guards on persistent data), with the service running in the foreground as PID 1
- Credentials handled with **Docker secrets** (`/run/secrets`) and `.env` for non-sensitive settings, none of them committed
- A dedicated bridge network (only port 443 exposed) and two named volumes persisted on the host
- Everything driven by a `Makefile` (`make`, `down`, `clean`, `fclean`, `re`)
- Written user and developer documentation (`USER_DOC.md`, `DEV_DOC.md`)

**Link:** https://github.com/Gmasfisch/gustavo-portfolio/inception

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

I am currently **rank 06**, having completed core system-level projects including Minishell, Philosophers, Webserver and Inception.

---

# 📄 Download CV

You can download my resume here :

**➡️ [CV (English)](docs/Gustavo_Fischbach_CV_EN.pdf)**  
**➡️ [CV (Deutsch)](docs/Gustavo_Fischbach_CV_DE.pdf)**

---

# 🇩🇪 Kurzprofil (für deutsche Recruiter)

- Junior Software Developer in Ausbildung bei **42 Berlin (rank 06)**
- Schwerpunkt: **C, C++, Linux, Systemprogrammierung, Netzwerkprogrammierung, Concurrency, Speicherverwaltung**
- Erfahrung in internationalen und multikulturellen Teams
- Sprachen: **Spanisch (Muttersprache), Englisch (fließend), Deutsch (B2)**
- Interesse an Backend, Systemprogrammierung, Embedded oder Low-Level Development, SAP ABAP.

---

# 📬 Contact

- GitHub: https://github.com/Gmasfisch
- Email: fischbachgustavo@gmail.com
- Location: Berlin, Germany

---

Thank you for visiting my portfolio!  
I'm actively seeking Software Developer positions and opportunities to grow as a software engineer.
