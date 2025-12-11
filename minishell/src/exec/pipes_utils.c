/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:09:17 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:24 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	setup_ipc(t_pipectx *c)
{
	if (c->n <= 1)
		return (0);
	c->pipes = alloc_pipes(c->n - 1);
	if (!c->pipes)
		return (perror("pipe alloc"), 1);
	c->pids = (pid_t *)malloc(sizeof(pid_t) * c->n);
	if (!c->pids)
	{
		close_all_pipes(c->pipes, c->n - 1);
		free_pipes(c->pipes, c->n - 1);
		c->pipes = NULL;
		return (1);
	}
	return (0);
}

static int	spawn_children(t_pipectx *c)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < c->n)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			set_signals_child_defaults();
			child_wire_fds(i, c->n, c->pipes);
			exit(execute_node(c->stages[i]));
		}
		c->pids[i++] = pid;
	}
	return (0);
}

static int	wait_and_finish(t_pipectx *c)
{
	int	rc;

	rc = wait_all_and_get_last(c->pids, c->n);
	if (c->pids)
	{
		free(c->pids);
		c->pids = NULL;
	}
	set_signals_parent_idle();
	handle_sigint_feedback();
	if (c->n > 0)
		ms_update_underscore_from_node(c->stages[c->n - 1]);
	return (rc);
}

static int	fail_fork(t_pipectx *c)
{
	perror("fork");
	parent_close_pipes(c);
	if (c->pids)
	{
		free(c->pids);
		c->pids = NULL;
	}
	set_signals_parent_idle();
	handle_sigint_feedback();
	return (1);
}

int	exec_pipeline_root(t_node *root)
{
	t_pipectx	c;
	int			status;

	if (init_ctx(&c, root))
		return (0);
	if (c.n <= 0)
		return (0);
	if (c.n == 1)
		return (execute_node(c.stages[0]));
	if (setup_ipc(&c))
		return (1);
	set_signals_parent_exec();
	if (spawn_children(&c) < 0)
		return (fail_fork(&c));
	parent_close_pipes(&c);
	status = wait_and_finish(&c);
	return (status);
}
