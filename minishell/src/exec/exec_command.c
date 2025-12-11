/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:50:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:14 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	exec_node_command(t_node *node, char ***envp)
{
	char	**expanded;
	int		status;

	if (!node || !node->cmd_args)
		return (0);
	expanded = expand_tokens(node->cmd_args);
	if (!expanded)
		return (1);
	if (!expanded[0])
	{
		free_split(expanded);
		return (0);
	}
	ms_update_underscore_from_args(expanded);
	if (is_builtin(expanded[0]))
		status = execute_builtin(expanded, envp);
	else
		status = execute_command(expanded, envp);
	free_split(expanded);
	return (status);
}
