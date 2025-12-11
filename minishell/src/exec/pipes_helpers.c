/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:40:19 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 19:20:54 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	parent_close_pipes(t_pipectx *c)
{
	if (c->n > 1 && c->pipes)
	{
		close_all_pipes(c->pipes, c->n - 1);
		free_pipes(c->pipes, c->n - 1);
		c->pipes = NULL;
	}
}

void	wctx_init(t_wctx *w, pid_t *pids, int n)
{
	w->n = n;
	w->waited = 0;
	w->last_status = 0;
	w->last_pid = pids[n - 1];
	w->saw_sigint = 0;
}

void	free_pipes(int **pipes, int n_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < n_pipes)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

static int	close_pair(int *p)
{
	int	ret;

	ret = 0;
	if (p[0] >= 0 && close(p[0]) == -1)
		ret = -1;
	if (p[1] >= 0 && close(p[1]) == -1)
		ret = -1;
	return (ret);
}

void	close_all_pipes(int **pipes, int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		if (pipes[i])
			close_pair(&pipes[i][0]);
		i++;
	}
}
