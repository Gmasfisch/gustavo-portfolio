/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:55:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 00:55:00 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_node	*create_group_node(char **tokens, int start, int end)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = NODE_GROUP;
	node->heredoc_fd = -1;
	node->heredoc_collected = 0;
	node->line_no = current_line_number();
	node->left = parser(tokens, start + 1, end - 1);
	node->right = NULL;
	node->cmd_args = NULL;
	node->filename = NULL;
	return (node);
}

static t_node	*create_simple_command(char **tokens, int start, int end)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = get_token_type(tokens[start]);
	node->cmd_args = copy_tokens(tokens, start, end);
	node->heredoc_fd = -1;
	node->heredoc_collected = 0;
	node->line_no = current_line_number();
	node->left = NULL;
	node->right = NULL;
	node->filename = NULL;
	return (node);
}

t_node	*create_command_or_group(char **tokens, int start, int end)
{
	if (ft_strcmp(tokens[start], "(") == 0
		&& ft_strcmp(tokens[end], ")") == 0)
		return (create_group_node(tokens, start, end));
	return (create_simple_command(tokens, start, end));
}

t_node	*alloc_op_node(char **tokens, int op_index)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = get_token_type(tokens[op_index]);
	node->cmd_args = NULL;
	node->heredoc_fd = -1;
	node->heredoc_collected = 0;
	node->line_no = current_line_number();
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*create_operator_node(char **tokens, int start, int end, int op_index)
{
	t_node_type	type;
	t_node		*node;

	type = get_token_type(tokens[op_index]);
	if (type == NODE_PIPE || type == NODE_AND || type == NODE_OR)
		return (handle_logic_op(tokens, start, end, op_index));
	if (type == NODE_REDIR_OUT || type == NODE_REDIR_APPEND
		|| type == NODE_REDIR_IN || type == NODE_HEREDOC)
		return (handle_redir_op(tokens, start, end, op_index));
	node = alloc_op_node(tokens, op_index);
	if (!node)
		return (NULL);
	node->left = parser(tokens, start, op_index - 1);
	node->right = parser(tokens, op_index + 1, end);
	return (node);
}
