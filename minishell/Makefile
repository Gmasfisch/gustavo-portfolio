CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes
RM			= rm -f
NAME		= minishell
LIBFT		= ./libft/libft.a
SRCS		= main.c					\
				process_line.c 				\
				utils/parser_utils.c		\
				utils/utils.c				\
				utils/tokenizer_utils.c 	\
				utils/clean.c \
				utils/env_utils.c \
				utils/env_set.c \
				src/status_utils.c		\
				src/status.c \
				utils/expansion_utils.c		\
				utils/wildcard_handler_utils.c	\
				src/parser_helpers.c				\
				src/parser.c				\
				src/parser_nodes.c				\
				src/parser_tokens.c			\
				src/tokenizer.c			\
				src/expansion_helpers.c \
				src/expansion_core.c \
				src/expansion_tokens.c \
				src/expansion_handlers.c \
				src/exec/exec_helpers.c \
				src/exec/exec.c \
				src/exec/exec_update.c \
				src/exec/exec_command.c \
				src/exec/exec_redir_simple.c \
				src/exec/exec_logic.c \
				src/exec/built_in/built_in.c \
				src/exec/built_in/built_in_utils.c \
				src/exec/built_in/cd_helpers.c \
				src/exec/built_in/cd.c \
				src/exec/built_in/echo.c \
				src/exec/built_in/env.c \
				src/exec/built_in/exit.c \
				src/exec/built_in/export.c \
				src/exec/built_in/export_identifier.c \
				src/exec/built_in/export_store.c \
				src/exec/built_in/pwd.c \
				src/exec/built_in/unset.c \
				src/exec/path.c \
				src/exec/redir_heredoc_writer.c \
				src/exec/redir_heredoc_writer_helper.c	\
				src/exec/redir_heredoc_pipe.c \
				src/exec/redir_heredoc_collect.c \
				src/exec/redir_heredoc_exec.c \
				src/exec/pipes.c \
				src/exec/pipes_helpers.c \
				src/exec/pipes_utils.c \
				src/exec/pipes_wait_last.c \
				src/wildcard_handler.c \
				src/in_out/in_out_utils.c \
				src/in_out/in_out_utils_next.c \
				src/in_out/redir_in.c \
				src/in_out/redir_out.c \
				src/signals_status.c \
			src/signals_term.c \
			src/signals_term_restore.c \
			src/signals_handler.c \
			src/signals_parent.c \
			src/signals_parent_utils.c \

OBJS		= $(SRCS:.c=.o)

READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null)
CFLAGS  += -I$(READLINE_PREFIX)/include
LDFLAGS = -L$(READLINE_PREFIX)/lib -lreadline -lncurses

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(LIBFT) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
			make bonus -C ./libft

clean:
			make clean -C ./libft
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C ./libft
			$(RM) $(NAME)

re:			fclean all
