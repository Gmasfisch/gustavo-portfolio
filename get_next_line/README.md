# Get Next Line

A line-reading utility implemented in C as part of the 42 Berlin curriculum.  

---

## Overview

get_next_line is a function that reads from a file descriptor one line at a time, returning each line as a dynamically allocated string until EOF.  

This project strengthened my understanding of buffer management, memory allocation, static variables, and efficient file I/O.  

**Course:** 42 Berlin — 2025 (Rank 01)  

---

## Key Features

- Reads one complete line per function call  
- Works with:  
  - Regular files  
  - Standard input  
  - Pipes and other file descriptors  
- Handles arbitrarily long lines  
- Efficient buffered reading  
- No memory leaks  
- Fully C-standard compliant   

### Bonus Features

✔ Multiple File Descriptor Support

- The bonus version supports up to 4096 file descriptors at the same time.
- Each FD keeps its own internal buffer using a static array
- Reading from different files never interferes
- Perfect for parallel file reads  
- Same interface as mandatory  
- Safely handles leftover data across calls  

---

## How It Works

How It Works

- Static storage holds data between calls  
- Buffered reads reduce system calls  
- Line extraction logic returns everything up to \n  
- Leftover management saves remaining text for the next call  
- Memory-safe design prevents leaks or pointer issues  

---

## Usage

Include the header and compile the source files inside your own project.
```bash
#include "get_next_line.h"

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```
## Compile Example  
gcc -Wall -Wextra -Werror \
    get_next_line.c get_next_line_utils.c \
    main.c  

## Bonus Version
gcc -Wall -Wextra -Werror \
    get_next_line_bonus.c get_next_line_utils_bonus.c \
    main.c  

## Learning Outcomes

- Handling persistent state with static variables  
- Efficient buffer and string manipulation  
- Managing multiple file descriptors  
- Building robust I/O utilities in C  
- Memory management discipline

Project Status

✅ Completed (includes all mandatory and bonus requirements).

Author / Contact

Gustavo Fischbach — 42 Berlin (rank 04)  
**GitHub Portfolio:** [Portfolio](https://github.com/Gmasfisch/gustavo-portfolio)  
**GitHub Profile:** [Profile](https://github.com/Gmasfisch)  
**Email:** fischbachgustavo@gmail.com