/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:00:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/21 13:39:09 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	store_or_expand(char **arr, int *idx, const char *buf)
{
	char	*dup;

	dup = ft_strdup(buf);
	if (!dup)
		return ;
	if (ft_strchr(dup, '*'))
	{
		arr[*idx] = NULL;
		handle_wildcard(arr, dup, idx);
		free(dup);
	}
	else
	{
		arr[*idx] = dup;
		(*idx)++;
	}
}

void	handle_expansion(char *token, char **new_array, int *array_index)
{
	char	buf[4096];
	int		i;
	int		buf_index;

	i = 0;
	buf_index = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			buf_index = copy_single_quotes(token, &i, buf, buf_index);
		else if (token[i] == '\"')
			buf_index = copy_double_quotes(token, &i, buf, buf_index);
		else
			buf_index = copy_unquoted(token, &i, buf, buf_index);
	}
	buf[buf_index] = '\0';
	store_or_expand(new_array, array_index, buf);
}

int	copy_single_quotes(char *token, int *i, char *buf, int buf_index)
{
	(*i)++;
	while (token[*i] && token[*i] != '\'')
		buf[buf_index++] = token[(*i)++];
	if (token[*i] == '\'')
		(*i)++;
	return (buf_index);
}

int	copy_double_quotes(char *token, int *i, char *buf, int buf_index)
{
	(*i)++;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
			buf_index = handle_var_expansion(token, i, buf, buf_index);
		else
			buf[buf_index++] = token[(*i)++];
	}
	if (token[*i] == '\"')
		(*i)++;
	return (buf_index);
}
