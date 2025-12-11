# Philosophers

An implementation of the classic Dining Philosophers problem, developed as part of the 42 Berlin curriculum.

This project explores concurrency, synchronization, thread management, and process coordination using POSIX APIs.

The project is divided into **two separate folders**, each with its own Makefile:

- `philo/` — Mandatory version (threads + mutexes)
- `philo_bonus/` — Bonus version (processes + semaphores)

---

## Overview

The Dining Philosophers problem illustrates common challenges in concurrent programming, such as deadlock, starvation, and resource-sharing.  
This project helped me develop a deeper understanding of concurrency control, timing accuracy, and safe inter-thread and inter-process communication.

**Course:** 42 Berlin — 2025 (Rank 03)  

---

## Folder Structure

philosophers/  
│
├── philosophers/ # Mandatory version (threads)
│ ├── Makefile  
│ ├── src/  
│ ├── includes/  
│ └── ...  
│
└── philosophers_bonus/ # Bonus version (processes)  
├── Makefile  
├── src/  
├── includes/  
└── ...  

Each folder is compiled **separately**, and each produces its own executable.  

---

## Key Features — Mandatory (Threads + Mutexes)

- Each philosopher runs as a **separate thread**  
- Forks protected with **mutexes**  
- Accurate timing and death detection  
- Avoids deadlock and starvation  
- Clean and deterministic shutdown  

---

## Key Features — Bonus (Processes + Semaphores)

- Each philosopher is a **separate process** created with `fork()`  
- Uses **POSIX semaphores** for synchronization between processes  
- Semaphores used to control:
  - Access to forks  
  - Logging output  
  - Meal-counting  
  - Death condition
- Death monitoring handled inside each philosopher process  
- Parent process waits on all children with `waitpid()`  
- No orphan or zombie processes  
- All times are in milliseconds

This version demonstrates deeper system-level knowledge of:

- Inter-process communication  
- Semaphore synchronization  
- Process lifecycle management  

---

## Installation & Build

### Mandatory version

```bash
# Clone repo
git clone https://github.com/Gmasfisch/gustavo-portfolio.git
cd gustavo-portfolio/philosophers/philosophers

cd philosophers
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required(optional)]  
# Example
Example:  
./philo 5 800 200 200 5(optional argument)
```

### Bonus version
```bash  
# Clone repo  
git clone https://github.com/Gmasfisch/gustavo-portfolio.git  
cd gustavo-portfolio/philosophers/  

cd philosophers_bonus  
make  
./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required(optional)]
# Example
./philo_bonus 5 800 200 200 5(optional argument)  
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
