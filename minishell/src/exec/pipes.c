/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:45:08 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:25 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	add_stage(t_node *n, t_node **stages, int *i, int max)
{
	if (!n)
		return (0);
	if (n->type == NODE_PIPE)
	{
		if (add_stage(n->left, stages, i, max))
			return (1);
		return (add_stage(n->right, stages, i, max));
	}
	if (*i >= max)
		return (1);
	stages[*i] = n;
	*i = *i + 1;
	return (0);
}

int	build_stages(t_node *root, t_node **stages, int max, int *out_n)
{
	int	i;

	*out_n = 0;
	if (!root || !stages || max <= 0)
		return (1);
	i = 0;
	if (add_stage(root, stages, &i, max))
		return (1);
	if (i <= 0)
		return (1);
	*out_n = i;
	return (0);
}

int	**alloc_pipes(int n_pipes)
{
	int		**pipes;
	int		i;

	pipes = malloc(sizeof(int *) * n_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			close_all_pipes(pipes, i);
			free_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	child_wire_fds(int i, int n, int **pipes)
{
	if (i > 0 && dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
		exit(1);
	if (i < n - 1 && dup2(pipes[i][1], STDOUT_FILENO) < 0)
		exit(1);
	close_all_pipes(pipes, n - 1);
}

int	execute_pipe(t_node *left, t_node *right)
{
	t_node	root;

	root.type = NODE_PIPE;
	root.left = left;
	root.right = right;
	root.cmd_args = NULL;
	root.filename = NULL;
	root.env = NULL;
	root.heredoc_fd = -1;
	root.heredoc_collected = 0;
	return (exec_pipeline_root(&root));
}
