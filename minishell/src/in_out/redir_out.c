/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:03:58 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:57:31 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/in_out.h"
#include "../../includes/signals.h"

static int	open_out(const char *filename, int append)
{
	if (append)
		return (open_write_append(filename));
	return (open_write_trunc(filename));
}

int	execute_redir_out(t_node *cmd, const char *file, int append)
{
	int		fd;
	pid_t	p;

	fd = open_out(file, append);
	if (fd < 0)
		return (1);
	ms_update_underscore_from_node(cmd);
	set_signals_parent_exec();
	p = fork();
	if (p < 0)
		return (ms_perror1("fork"), set_signals_parent_idle(),
			handle_sigint_feedback(), close_fd(fd), 1);
	if (p == 0)
	{
		set_signals_child_defaults();
		if (dup2_safe(fd, STDOUT_FILENO) < 0)
		{
			close_fd(fd);
			exit(1);
		}
		close_fd(fd);
		exit(execute_node(cmd));
	}
	return (close_fd(fd), set_signals_parent_idle(),
		handle_sigint_feedback(), wait_collect_exitcode(p));
}

int	execute_redir_out_parent(t_node *cmd, const char *file,
	int append)
{
	int	fd;
	int	saved[2];
	int	code;

	if (!cmd || !file)
		return (1);
	fd = open_out(file, append);
	if (fd < 0)
		return (1);
	if (save_stdio(saved) < 0)
	{
		close_fd(fd);
		return (1);
	}
	if (dup2_safe(fd, STDOUT_FILENO) < 0)
	{
		close_fd(fd);
		restore_stdio(saved);
		return (1);
	}
	close_fd(fd);
	code = execute_node(cmd);
	restore_stdio(saved);
	return (code);
}
