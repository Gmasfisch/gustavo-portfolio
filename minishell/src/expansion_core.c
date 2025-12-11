/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:00:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/21 13:36:17 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**expansion(char **args)
{
	char	**new;
	int		i;
	int		idx;

	new = malloc(sizeof(char *) * 256);
	if (!new)
		return (NULL);
	i = 0;
	idx = 0;
	while (args[i])
	{
		handle_expansion(args[i], new, &idx);
		free(args[i]);
		i++;
	}
	new[idx] = NULL;
	free(args);
	return (new);
}

char	**expansion_heredoc(char **args)
{
	char	**new;
	int		i;
	int		idx;

	new = malloc(sizeof(char *) * 256);
	if (!new)
		return (NULL);
	i = 0;
	idx = 0;
	while (args[i])
	{
		handle_expansion_heredoc(args[i], new, &idx);
		free(args[i]);
		i++;
	}
	new[idx] = NULL;
	free(args);
	return (new);
}

void	handle_expansion_heredoc(char *token, char **new_array,
			int *array_index)
{
	char	buf[4096];
	int		i;
	int		buf_index;

	i = 0;
	buf_index = 0;
	while (token[i])
		buf_index = copy_unquoted(token, &i, buf, buf_index);
	buf[buf_index] = '\0';
	store_or_expand(new_array, array_index, buf);
}

char	**tokenizer_heredoc(char *line)
{
	char	**tokens;
	int		line_index;
	int		token_index;

	tokens = malloc(sizeof(char *) * 256);
	if (!tokens)
		return (NULL);
	line_index = 0;
	token_index = 0;
	while (line[line_index])
		tokens[token_index++] = copy_word_heredoc(line, &line_index);
	tokens[token_index] = NULL;
	return (tokens);
}

char	*copy_word_heredoc(char *line, int *line_index)
{
	char	*token;
	int		token_index;

	token_index = 0;
	token = malloc(4096);
	if (!token)
		return (NULL);
	while (line[*line_index] && !search_double_operator(line, line_index)
		&& !search_single_operator(line, line_index))
		token[token_index++] = line[(*line_index)++];
	token[token_index] = '\0';
	return (token);
}
