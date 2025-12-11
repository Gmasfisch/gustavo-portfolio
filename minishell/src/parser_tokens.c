/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:55:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 00:55:00 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node_type	get_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (NODE_PIPE);
	if (ft_strcmp(token, "&&") == 0)
		return (NODE_AND);
	if (ft_strcmp(token, "||") == 0)
		return (NODE_OR);
	if (ft_strcmp(token, "<") == 0)
		return (NODE_REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (NODE_REDIR_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (NODE_REDIR_APPEND);
	if (ft_strcmp(token, "<<") == 0)
		return (NODE_HEREDOC);
	return (NODE_COMMAND);
}
