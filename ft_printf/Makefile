NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror -I../Libft
CC = cc 

CFILES = ft_printf.c p_num.c p_string.c p_address.c p_unsigned.c p_hex.c
OBJ	= $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re