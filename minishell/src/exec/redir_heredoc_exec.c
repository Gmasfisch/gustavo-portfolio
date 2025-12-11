/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:45:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:27:16 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/signals.h"

int	heredoc_reader_process(int pipefd[2], char *delimiter);

static int	run_heredoc_command(t_node *cmd, int read_fd)
{
	pid_t	child;
	int		status;

	ms_update_underscore_from_node(cmd);
	set_signals_parent_exec();
	child = fork();
	if (child < 0)
		return (close(read_fd),
			set_signals_parent_idle(), handle_sigint_feedback(), 1);
	if (child == 0)
	{
		set_signals_child_defaults();
		if (dup2(read_fd, STDIN_FILENO) == -1)
		{
			close(read_fd);
			exit(1);
		}
		close(read_fd);
		execute_node(cmd);
		exit(1);
	}
	close(read_fd);
	status = wait_collect_exitcode(child);
	set_signals_parent_idle();
	return (handle_sigint_feedback(), status);
}

int	execute_heredoc(t_node *heredoc, t_node *cmd)
{
	int	pipefd[2];
	int	status;

	if (!heredoc)
		return (1);
	if (heredoc->heredoc_collected && heredoc->heredoc_fd >= 0)
	{
		status = run_heredoc_command(cmd, heredoc->heredoc_fd);
		heredoc->heredoc_fd = -1;
		heredoc->heredoc_collected = 0;
		return (status);
	}
	status = heredoc_reader_process(pipefd, heredoc->filename);
	if (status == -2)
		return (130);
	if (status != 0)
		return (1);
	return (run_heredoc_command(cmd, pipefd[0]));
}
