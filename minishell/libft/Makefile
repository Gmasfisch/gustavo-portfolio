CC			= cc
CFLAGS		= -Wall -Wextra -Werror
NAME		= libft.a
RM			= rm -f
SRCS		= ./ft_atoi.c \
				./ft_bzero.c \
				./ft_calloc.c \
				./ft_isalnum.c \
				./ft_isalpha.c \
				./ft_isascii.c \
				./ft_isdigit.c \
				./ft_isprint.c \
				./ft_itoa.c \
				./ft_memchr.c \
				./ft_memcmp.c \
				./ft_memcpy.c \
				./ft_memmove.c \
				./ft_memset.c \
				./ft_putchar_fd.c \
				./ft_putendl_fd.c \
				./ft_putnbr_fd.c \
				./ft_putstr_fd.c \
				./ft_split.c \
				./ft_strchr.c \
				./ft_strdup.c \
				./ft_striteri.c \
				./ft_strjoin.c \
				./ft_strlcat.c \
				./ft_strlcpy.c \
				./ft_strncpy.c \
				./ft_strlen.c \
				./ft_strmapi.c \
				./ft_strncmp.c \
				./ft_strnstr.c \
				./ft_strrchr.c \
				./ft_strtrim.c \
				./ft_substr.c \
				./ft_tolower.c \
				./ft_toupper.c \
				./ft_strcmp.c \

SRCS_PRINTF = ./ft_printf.c \
					./type_csdp.c \
					./type_ptr.c \
					./type_u.c \
					./type_x_upx.c \
				
SRCSBONUS	= ./ft_lstnew.c \
				./ft_lstadd_front.c \
				./ft_lstsize.c \
				./ft_lstlast.c \
				./ft_lstadd_back.c \
				./ft_lstdelone.c \
				./ft_lstclear.c \
				./ft_lstiter.c \
				./ft_lstmap.c \

OBJS		= $(SRCS:.c=.o)
OBJS_PRINTF	= $(SRCS_PRINTF:.c=.o)
OBJSBONUS	= $(SRCSBONUS:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

all: 		$(NAME)

$(NAME): 	$(OBJS) $(OBJS_PRINTF)
			ar -rc $(NAME) $(OBJS) $(OBJS_PRINTF)

clean:
			rm -f $(OBJS) $(OBJS_PRINTF) $(OBJSBONUS)

fclean: 	clean
			rm -f $(NAME)

re: 		fclean all

bonus:		$(OBJS) $(OBJS_PRINTF) $(OBJSBONUS)
			ar -rc $(NAME) $(OBJS) $(OBJS_PRINTF) $(OBJSBONUS)