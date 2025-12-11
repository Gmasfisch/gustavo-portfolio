/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:45:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 20:44:53 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/signals.h"
#include <errno.h>

void	heredoc_write_loop(int write_fd, char *delimiter);

static int	prepare_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return (1);
	set_signals_parent_heredoc();
	return (0);
}

pid_t	fork_heredoc_writer(int pipefd[2], char *delimiter)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(pipefd[0]);
		heredoc_write_loop(pipefd[1], delimiter);
	}
	close(pipefd[1]);
	return (pid);
}

static int	wait_heredoc_writer(pid_t pid, int read_fd)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		close(read_fd);
		set_signals_parent_idle();
		handle_sigint_feedback();
		return (1);
	}
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(read_fd);
		set_signals_parent_idle();
		handle_sigint_feedback();
		return (-2);
	}
	set_signals_parent_idle();
	handle_sigint_feedback();
	return (0);
}

int	heredoc_reader_process(int pipefd[2], char *delimiter)
{
	pid_t	pid;

	if (prepare_heredoc_pipe(pipefd))
		return (1);
	pid = fork_heredoc_writer(pipefd, delimiter);
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		set_signals_parent_idle();
		handle_sigint_feedback();
		return (1);
	}
	return (wait_heredoc_writer(pid, pipefd[0]));
}
