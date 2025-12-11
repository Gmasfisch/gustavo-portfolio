/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:50:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/21 11:41:38 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	ms_try_set_from_path(char **argv)
{
	char	*path;

	path = ft_get_cmd_path(copy_env(NULL), argv[0]);
	if (!path)
		return (0);
	env_set("_", path);
	free(path);
	return (1);
}

void	ms_update_underscore_from_args(char **argv)
{
	if (!argv || !argv[0])
		return ;
	if (ms_try_set_from_path(argv))
		return ;
	env_set("_", argv[0]);
}

static t_node	*ms_find_command_node(t_node *node)
{
	t_node	*candidate;

	if (!node)
		return (NULL);
	if (node->type == NODE_COMMAND)
		return (node);
	if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND || node->type == NODE_HEREDOC)
	{
		candidate = ms_find_command_node(node->left);
		if (candidate)
			return (candidate);
		return (ms_find_command_node(node->right));
	}
	if (node->type == NODE_GROUP)
		return (ms_find_command_node(node->left));
	return (NULL);
}

void	ms_update_underscore_from_node(t_node *node)
{
	t_node	*cmd;
	char	**expanded;

	cmd = ms_find_command_node(node);
	if (!cmd || !cmd->cmd_args)
		return ;
	expanded = expand_tokens(cmd->cmd_args);
	if (!expanded)
		return ;
	if (expanded[0])
		ms_update_underscore_from_args(expanded);
	free_split(expanded);
}
