/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:50:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:19 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static t_node	*redir_target(t_node *n)
{
	if (!n)
		return (NULL);
	if (n->left)
		return (n->left);
	if (n->right)
		return (n->right);
	return (NULL);
}

static char	*expand_redir_filename(const char *raw, int *ambiguous)
{
	char	*tmp[2];
	char	**expanded;
	char	*result;
	int		count;

	*ambiguous = 0;
	if (!raw)
		return (NULL);
	tmp[0] = (char *)raw;
	tmp[1] = NULL;
	expanded = expand_tokens(tmp);
	if (!expanded)
		return (NULL);
	count = count_tokens(expanded);
	if (count != 1)
	{
		if (count > 1)
			*ambiguous = 1;
		result = NULL;
	}
	else
		result = ft_strdup(expanded[0]);
	free_split(expanded);
	return (result);
}

static int	run_redir(t_node *n, t_node *cmd, char *filename)
{
	if (n->type == NODE_REDIR_IN)
	{
		if (is_builtin_cmd_node(cmd))
			return (execute_redir_in_parent(cmd, filename));
		return (execute_redir_in(cmd, filename));
	}
	if (n->type == NODE_REDIR_OUT)
	{
		if (is_builtin_cmd_node(cmd))
			return (execute_redir_out_parent(cmd, filename, 0));
		return (execute_redir_out(cmd, filename, 0));
	}
	if (is_builtin_cmd_node(cmd))
		return (execute_redir_out_parent(cmd, filename, 1));
	return (execute_redir_out(cmd, filename, 1));
}

int	exec_node_redir(t_node *n)
{
	t_node	*cmd;
	char	*filename;
	int		ambiguous;
	int		status;

	if (!n)
		return (0);
	cmd = redir_target(n);
	if (!cmd || !n->filename)
		return (0);
	if (n->type == NODE_HEREDOC)
		return (execute_heredoc(n, cmd));
	filename = expand_redir_filename(n->filename, &ambiguous);
	if (ambiguous)
	{
		write(2, "minishell: ambiguous redirect\n", 31);
		set_shell_status(1);
		return (1);
	}
	if (!filename)
		return (1);
	status = run_redir(n, cmd, filename);
	free(filename);
	return (status);
}
