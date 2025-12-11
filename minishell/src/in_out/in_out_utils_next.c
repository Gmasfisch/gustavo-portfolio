/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:03:58 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 01:01:09 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/in_out.h"

int	dup2_safe(int from, int to)
{
	if (dup2(from, to) < 0)
	{
		if (to == STDIN_FILENO)
			ms_perror1("dup2(STDIN)");
		else if (to == STDOUT_FILENO)
			ms_perror1("dup2(STDOUT)");
		else
			ms_perror1("dup2");
		return (-1);
	}
	return (0);
}

int	close_fd(int fd)
{
	if (fd >= 0 && close(fd) < 0)
	{
		ms_perror1("close");
		return (-1);
	}
	return (0);
}

int	wait_collect_exitcode(pid_t pid)
{
	int	status;
	int	sig;

	if (waitpid(pid, &status, 0) < 0)
	{
		ms_perror1("waitpid");
		return (130);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (128 + sig);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	save_stdio(int saved[2])
{
	saved[0] = dup(STDIN_FILENO);
	saved[1] = dup(STDOUT_FILENO);
	if (saved[0] < 0 || saved[1] < 0)
	{
		ms_perror1("dup(save stdio)");
		return (-1);
	}
	return (0);
}

int	restore_stdio(int saved[2])
{
	int	ok;

	ok = 0;
	if (dup2_safe(saved[0], STDIN_FILENO) < 0)
		ok = -1;
	if (dup2_safe(saved[1], STDOUT_FILENO) < 0)
		ok = -1;
	if (close_fd(saved[0]) < 0)
		ok = -1;
	if (close_fd(saved[1]) < 0)
		ok = -1;
	return (ok);
}
