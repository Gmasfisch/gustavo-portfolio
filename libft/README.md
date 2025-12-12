# Libft

A foundational custom C library that re-implements selected parts of the C standard library and provides small helper utilities.  
Created as part of the 42 Berlin curriculum.

---

## Overview

libft reproduces the behavior of common libc functions so you fully understand how they work under the hood.  
This project helped me master:

- Manual memory management and heap usage
- String handling and edge cases
- Character classification and conversion
- Writing tiny, reusable C modules
- Basic generic data structures (linked lists — bonus)

**Course:** 42 Berlin — 2025 (Rank 02)

---

## Key Features — Mandatory

- Re-implemented essential functions from the C standard library:
  - Character checks and transforms (`is*`, `to*`)
  - Memory functions (`mem*`, `bzero`, `calloc`)
  - String utilities (`strlen`, `strlcpy`, `strlcat`, `str*`, `strncmp`, `strnstr`, `strdup`, etc.)
  - Conversions (`atoi`, `itoa`)
  - File descriptor helpers (write functions)
- Safe, edge-case-aware implementations
- Single public header: `libft.h`
- Portable and easy to include in future projects

---

## Key Features — Bonus

- Singly linked list API:
  - `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`
  - `ft_lstsize`, `ft_lstlast`
  - `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`
- Generic `void *content` nodes for flexible usage
- Thorough memory cleanup helpers

---

## Architecture & Design

- Each function implemented from scratch following the project rules (only allowed libc functions used)
- Clear separation between modules (char, mem, str, fd, list)
- Defensive programming: checks for `NULL`, proper freeing on error paths
- Header `libft.h` exposes the API; implementations live in `src/`
- Makefile automates build, clean and rebuild operations

## Installation & Build

### Mandatory version

```bash
# Clone repo
git clone https://github.com/Gmasfisch/gustavo-portfolio.git
cd gustavo-portfolio/libft
make

# Example usage (compile a test program with the library)
gcc main.c libft.a -o my_program

# Example: link libft into a small program
# (create main.c that calls e.g. ft_strlen / ft_putstr_fd, then:)
gcc main.c libft.a -o test_libft
./test_libft
```

## Learning Outcomes

- Deep understanding of low-level string and memory operations
- Correct dynamic allocation and ownership patterns
- Writing predictable, well-documented C functions
- Building a small, reusable library used across other 42 projects (ft_printf, get_next_line, pipex)

Author / Contact

Gustavo Fischbach — 42 Berlin (rank 04)  
**GitHub Portfolio:** [Portfolio](https://github.com/Gmasfisch/gustavo-portfolio)  
**GitHub Profile:** [Profile](https://github.com/Gmasfisch)  
**Email:** fischbachgustavo@gmail.com
