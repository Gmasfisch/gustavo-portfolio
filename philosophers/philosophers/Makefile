CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
SRC = main.c \
	  ft_atoi.c \
	  actions.c \
	  actions2.c \
	  utils.c \
	  threads.c \
	  init.c \
	  helpers.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

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