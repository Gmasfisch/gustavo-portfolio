/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_writer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:45:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/21 14:05:31 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <errno.h>
#include <fcntl.h>

static int	redirect_stdout_to_tty(int saved)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_WRONLY);
	if (tty_fd < 0)
		return (0);
	if (dup2(tty_fd, STDOUT_FILENO) == -1)
	{
		close(tty_fd);
		restore_stdout(saved);
		return (1);
	}
	close(tty_fd);
	return (0);
}

static void	print_heredoc_warning(const char *delimiter, int line_no)
{
	char	*num;

	if (line_no <= 0)
		return ;
	write(STDERR_FILENO,
		"minishell: warning: here-document at line ",
		sizeof("minishell: warning: here-document at line ") - 1);
	num = ft_itoa(line_no);
	if (!num)
		return ;
	write(STDERR_FILENO, num, ft_strlen(num));
	write(STDERR_FILENO,
		" delimited by end-of-file (wanted `",
		sizeof(" delimited by end-of-file (wanted `") - 1);
	write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
	write(STDERR_FILENO, "')\n", sizeof("')\n") - 1);
	free(num);
}

static int	handle_heredoc_eof(int saved, const char *delimiter, int line_no)
{
	int	status;

	if (errno == EINTR)
		status = 130;
	else
	{
		print_heredoc_warning(delimiter, line_no);
		status = 0;
	}
	restore_stdout(saved);
	return (status);
}

static void	print_args(char **args, int write_fd)
{
	int	i;

	i = 0;
	while (args[i])
	{
		write(write_fd, args[i], ft_strlen(args[i]));
		i++;
	}
	write(write_fd, "\n", 1);
}

void	heredoc_write_loop(int write_fd, char *delimiter)
{
	char	*line;
	int		saved_stdout;
	char	**args;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0 || redirect_stdout_to_tty(saved_stdout))
		exit(1);
	while (1)
	{
		errno = 0;
		line = readline("> ");
		if (!line)
			exit(handle_heredoc_eof(saved_stdout, delimiter,
					current_line_number()));
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			restore_stdout(saved_stdout);
			exit(0);
		}
		args = expansion_heredoc(tokenizer_heredoc(line));
		print_args(args, write_fd);
		free_split(args);
		free(line);
	}
}
