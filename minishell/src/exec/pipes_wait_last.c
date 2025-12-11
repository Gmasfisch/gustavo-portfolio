/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_wait_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:25:19 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 22:46:44 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	w_status_to_code(int status)
{
	int	code;

	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		code = 128 + WTERMSIG(status);
	else
		code = 1;
	return (code);
}

static void	check_status(t_wctx *w, int status)
{
	int	sig;

	sig = 0;
	w->last_status = status;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
}

static int	wctx_step(t_wctx *w)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(-1, &status, 0);
	if (wpid == -1)
	{
		if (errno == EINTR)
			return (0);
		return (1);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		w->saw_sigint = 1;
	if (wpid == w->last_pid)
		check_status(w, status);
	w->waited++;
	if (w->waited >= w->n)
		return (1);
	return (0);
}

static int	wctx_finish(const t_wctx *w)
{
	if (w->saw_sigint)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		return (130);
	}
	return (w_status_to_code(w->last_status));
}

int	wait_all_and_get_last(pid_t *pids, int n)
{
	t_wctx	w;

	wctx_init(&w, pids, n);
	while (!wctx_step(&w))
		;
	return (wctx_finish(&w));
}
