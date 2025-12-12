# ft_printf

A custom implementation of the standard `printf` function in C.  
Created as part of the 42 Berlin curriculum.

---

## Overview

`ft_printf` recreates the core behavior of the original `printf` function, allowing formatted output with variable arguments.  
This project helped me master:

- Variadic functions (`stdarg.h`)
- Format parsing and placeholder handling
- Type conversion and printing
- Buffering and edge-case management
- Clean modular C architecture

**Course:** 42 Berlin — 2025 (Rank 01)

---

## Key Features — Mandatory

- Full support for the following conversion specifiers:
  - `%c` — character
  - `%s` — string
  - `%p` — pointer address
  - `%d` / `%i` — signed integers
  - `%u` — unsigned integers
  - `%x` / `%X` — lowercase / uppercase hex
  - `%%` — print a literal `%`
- Handles all required flags defined in the 42 subject
- Safe and predictable behavior even with NULL pointers and edge cases

---

## Architecture & Design

- **Dispatcher-based architecture:**  
  Each format specifier is routed to its own print function (e.g., `print_char`, `print_hex`, etc.)
- **Format parser:**  
  Walks through the format string and interprets `%` sequences.
- **Variadic argument handling:**  
  Uses `va_list`, `va_start`, and `va_arg` to extract arguments dynamically.
- **Modular directory layout:**  
  Clean separation between parser, printers, and utils.
- **Return value:**  
  Accurately counts and returns the number of printed characters, matching `printf` behavior.

---

## Installation & Build

### Build the library

```bash
# Clone repo
git clone https://github.com/Gmasfisch/gustavo-portfolio.git
cd gustavo-portfolio/ft_printf
make
This produces:
libftprintf.a

Using ft_printf in your project
bash

gcc main.c libftprintf.a -o my_program
Makefile rules
bash

make        # build
make clean  # remove object files
make fclean # remove objects + library
make re     # rebuild
Example Usage

c
#include "ft_printf.h"

int main(void)
{
    int n = 42;
    ft_printf("Hello %s! Number: %d, Hex: %x\n", "world", n, n);
    return 0;
}
Output:

yaml
Hello world! Number: 42, Hex: 2a
```

## Learning Outcomes

- Implementing a real standard library function
- Designing a robust parser
- Working with variadic arguments in C
- Managing edge cases and output consistency
- Clean modular design and reusable printing functions

Author / Contact

Gustavo Fischbach — 42 Berlin (rank 04)  
**GitHub Portfolio:** [Portfolio](https://github.com/Gmasfisch/gustavo-portfolio)  
**GitHub Profile:** [Profile](https://github.com/Gmasfisch)  
**Email:** fischbachgustavo@gmail.com
