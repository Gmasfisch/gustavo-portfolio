NAME := pipex
BONUS_NAME := pipex_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror -I. -I../Libft

SRCS := main.c pipex.c execute.c path.c utils.c parser.c
OBJS := $(addprefix obj/, $(SRCS:.c=.o))

BONUS_SRCS := main_bonus.c pipex.c pipex_bonus.c path.c utils.c parser.c execute.c
BONUS_OBJS := $(addprefix obj/, $(BONUS_SRCS:.c=.o))

LIBFT_DIR := Libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	@:

clean:
	rm -f *.o
	rm -rf obj
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re