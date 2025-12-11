CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo_bonus
SRC	 = main.c \
	   actions.c \
	   fork_and_monitors.c \
	   utils.c \
	   clean.c \
	   init.c \
	   ft_atoi.c 
OBJ = $(SRC:.c=.o)
HEADER = philo_bonus.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re