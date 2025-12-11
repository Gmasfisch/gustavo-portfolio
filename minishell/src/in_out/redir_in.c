/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:03:58 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:41:14 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/in_out.h"
#include "../../includes/signals.h"

static int	helper_close_exit(int fd, int code)
{
	close_fd(fd);
	return (code);
}

int	execute_redir_in(t_node *cmd, const char *filename)
{
	int		fd;
	pid_t	p;
	int		code;

	(void)code;
	fd = open_readonly(filename);
	if (fd < 0)
		return (1);
	ms_update_underscore_from_node(cmd);
	set_signals_parent_exec();
	p = fork();
	if (p < 0)
		return (ms_perror1("fork"), close_fd(fd),
			set_signals_parent_idle(), handle_sigint_feedback(), 1);
	if (p == 0)
	{
		set_signals_child_defaults();
		if (dup2_safe(fd, STDIN_FILENO) < 0)
			exit(helper_close_exit(fd, 1));
		exit(helper_close_exit(fd, execute_node(cmd)));
	}
	return (close_fd(fd), set_signals_parent_idle(),
		handle_sigint_feedback(), wait_collect_exitcode(p));
}

int	execute_redir_in_parent(t_node *cmd, const char *filename)
{
	int	fd;
	int	saved[2];
	int	code;

	if (!cmd || !filename)
		return (1);
	fd = open_readonly(filename);
	if (fd < 0)
		return (1);
	if (save_stdio(saved) < 0)
	{
		close_fd(fd);
		return (1);
	}
	if (dup2_safe(fd, STDIN_FILENO) < 0)
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
