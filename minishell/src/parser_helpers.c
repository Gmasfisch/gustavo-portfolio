/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:57:13 by gfischba          #+#    #+#             */
/*   Updated: 2025/09/30 18:14:03 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/utils.h"

int		check_file(t_node *node, int op_index, int end);

static int	redir_set_filename(t_node *node, char **tok, int op_index, int end)
{
	if (check_file(node, op_index, end) == 1)
		return (1);
	node->filename = ft_strdup(tok[op_index + 1]);
	if (!node->filename)
	{
		free(node);
		return (1);
	}
	return (0);
}

static void	attach_leftmost(t_node *root, t_node *sub)
{
	t_node	*cur;

	if (!root)
		return ;
	cur = root;
	while (cur->left)
		cur = cur->left;
	cur->left = sub;
}

static t_node	*compose_redir_left(t_node *rest, t_node *base_cmd)
{
	if (rest)
	{
		if (base_cmd)
			attach_leftmost(rest, base_cmd);
		return (rest);
	}
	return (base_cmd);
}

t_node	*handle_logic_op(char **tok, int start, int end, int op_index)
{
	t_node	*node;

	node = alloc_op_node(tok, op_index);
	if (!node)
		return (NULL);
	node->left = parser(tok, start, op_index - 1);
	node->right = parser(tok, op_index + 1, end);
	return (node);
}

t_node	*handle_redir_op(char **tokens, int start, int end, int op_index)
{
	t_node	*node;
	t_node	*base_cmd;
	t_node	*rest;

	node = alloc_op_node(tokens, op_index);
	if (!node)
		return (NULL);
	if (redir_set_filename(node, tokens, op_index, end))
		return (NULL);
	base_cmd = NULL;
	if (start <= op_index - 1)
		base_cmd = parser(tokens, start, op_index - 1);
	rest = NULL;
	if (op_index + 2 <= end)
		rest = parser(tokens, op_index + 2, end);
	node->left = compose_redir_left(rest, base_cmd);
	return (node);
}
