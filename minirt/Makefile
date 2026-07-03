NAME        = miniRT

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
# Checking if X11 macOS file exists
IF_MACOS = $(shell [ -d /usr/X11/include ] && echo "-I/usr/X11/include")
IF_MACOS_LIB = $(shell [ -d /usr/X11/lib ] && echo "-L/usr/X11/lib")
INCLUDES    = -Iincludes -Iminilibx-linux $(IF_MACOS)
MLX_DIR     = minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx $(IF_MACOS_LIB) -lXext -lX11 -lm
LIBFT_DIR	= ./Libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS_DIR    = src
SRCS        = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/render.c \
	$(SRCS_DIR)/render_utils.c \
	$(SRCS_DIR)/lighting.c \
	$(SRCS_DIR)/shadowing.c \
	$(SRCS_DIR)/intersections.c \
	$(SRCS_DIR)/sphere.c \
	$(SRCS_DIR)/ray_operations.c \
	$(SRCS_DIR)/color_operations.c \
	$(SRCS_DIR)/helpers.c \
	$(SRCS_DIR)/helpers2.c \
	$(SRCS_DIR)/operations.c \
	$(SRCS_DIR)/operations2.c \
	$(SRCS_DIR)/operations3.c \
	$(SRCS_DIR)/parser.c \
	$(SRCS_DIR)/parser_utils.c \
	$(SRCS_DIR)/shape_parser.c \
	$(SRCS_DIR)/shape_parser_utils.c \
	$(SRCS_DIR)/cylinder.c \
	$(SRCS_DIR)/plane.c \
	$(SRCS_DIR)/window_management.c \
	$(SRCS_DIR)/rotation.c \
	$(SRCS_DIR)/rotation_utils.c \
	$(SRCS_DIR)/helpers3.c \
	$(SRCS_DIR)/cylinder_utils.c \
	$(SRCS_DIR)/ft_atof.c

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

$(LIBFT): | libft

$(MLX_LIB): | mlx

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft mlx