NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

CFILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_printf.c p_address.c p_hex.c \
		p_num.c p_string.c p_unsigned.c
BONUS_CFILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECTS = $(CFILES:.c=.o)
BONUS_OBJ = $(BONUS_CFILES:.c=.o)

all: $(NAME)

$(NAME):$(OBJECTS)
	$(AR) $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

bonus: $(BONUS_OBJ)
	$(AR) $(NAME) $^

clean:
	rm -rf $(OBJECTS) $(BONUS_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
