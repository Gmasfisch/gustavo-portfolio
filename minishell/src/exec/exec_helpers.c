/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 03:00:37 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 22:50:07 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_subshell(t_node *child)
{
	pid_t	pid;
	int		code;

	set_signals_parent_exec();
	pid = fork();
	if (pid < 0)
		return (ms_perror1("fork"), 1);
	if (pid == 0)
	{
		set_signals_child_defaults();
		code = execute_node(child);
		exit(code);
	}
	code = wait_all_and_get_last(&pid, 1);
	set_signals_parent_idle();
	handle_sigint_feedback();
	return (code);
}

int	check_node_type(t_node *node, char **env)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (status = exec_node_command(node, &env),
			set_shell_status(status), status);
	if (node->type == NODE_GROUP)
		return (status = execute_node(node->left),
			set_shell_status(status), status);
	if (node->type == NODE_PIPE)
		return (status = execute_pipe(node->left, node->right),
			set_shell_status(status), status);
	if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND || node->type == NODE_HEREDOC)
		return (status = exec_node_redir(node),
			set_shell_status(status), status);
	if (node->type == NODE_AND)
		return (status = exec_and(node->left, node->right),
			set_shell_status(status), status);
	if (node->type == NODE_OR)
		return (status = exec_or(node->left, node->right),
			set_shell_status(status), status);
	return (write(2, "Unknown node type\n", 19), 1);
}
