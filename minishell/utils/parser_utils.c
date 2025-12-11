/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:58:36 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/21 19:35:23 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_parenthesis(char **tokens, int i, int end)
{
	int	depth;

	depth = 1;
	i++;
	while (i <= end && depth > 0)
	{
		if (ft_strcmp(tokens[i], "(") == 0)
			depth++;
		else if (ft_strcmp(tokens[i], ")") == 0)
			depth--;
		i++;
	}
	return (i);
}

int	count_tokens(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	find_lowest_precedence(char **tokens, int start, int end)
{
	int			lowest_precedence;
	int			op_index;	
	int			i;
	t_node_type	type;

	lowest_precedence = 5;
	op_index = -1;
	i = start;
	while (i <= end)
	{
		if (ft_strcmp(tokens[i], "(") == 0)
			i = skip_parenthesis(tokens, i, end);
		else
		{
			type = get_token_type(tokens[i]);
			if (get_token_precedence(type) > 0
				&& get_token_precedence(type) < lowest_precedence)
			{
				lowest_precedence = get_token_precedence(type);
				op_index = i;
			}
			i++;
		}
	}
	return (op_index);
}

char	**copy_tokens(char **tokens, int start, int end)
{
	char	**cmd_args;
	int		tokens_count;
	int		i;

	if (start > end)
		return (NULL);
	i = 0;
	tokens_count = end - start + 1;
	cmd_args = malloc(sizeof(char *) * (tokens_count + 1));
	if (!cmd_args)
		return (NULL);
	while (start <= end)
	{
		cmd_args[i] = ft_strdup(tokens[start]);
		i++;
		start++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

int	get_token_precedence(t_node_type type)
{
	if (type == NODE_AND)
		return (1);
	if (type == NODE_OR)
		return (2);
	else if (type == NODE_PIPE)
		return (3);
	else if (type == NODE_REDIR_APPEND || type == NODE_REDIR_IN
		|| type == NODE_REDIR_OUT || type == NODE_HEREDOC)
		return (4);
	return (0);
}
