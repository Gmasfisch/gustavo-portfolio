/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:16:09 by gfischba          #+#    #+#             */
/*   Updated: 2025/09/24 10:05:25 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**tokenizer(char *line)
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
	{
		line_index = skip_spaces(line, line_index);
		if (!line[line_index])
			break ;
		if (line[line_index] == '\'' || line[line_index] == '"')
			tokens[token_index++] = handle_quotes(line, &line_index);
		else if (search_double_operator(line, &line_index))
			tokens[token_index++] = copy_operator(line, 2, &line_index);
		else if (search_single_operator(line, &line_index))
			tokens[token_index++] = copy_operator(line, 1, &line_index);
		else
			tokens[token_index++] = copy_word(line, &line_index);
	}
	tokens[token_index] = NULL;
	return (tokens);
}

int	skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

char	*handle_quotes(char *line, int *line_index)
{
	char	quote;
	char	*token;
	int		token_index;

	quote = line[*line_index];
	token = malloc(256);
	token_index = 0;
	token[token_index++] = quote;
	(*line_index)++;
	while (line[*line_index] && line[*line_index] != quote)
		token[token_index++] = line[(*line_index)++];
	if (line[*line_index] != quote)
	{
		free(token);
		write(2, "Error; missing closing quote\n", 30);
		return (NULL);
	}
	token[token_index++] = line[(*line_index)++];
	token[token_index] = '\0';
	return (token);
}
