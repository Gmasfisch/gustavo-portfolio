/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:37 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/21 13:37:44 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_double_operator(char *line, int *line_index)
{
	if ((line[*line_index] == '&' && line[(*line_index) + 1] == '&')
		|| (line[*line_index] == '|' && line[(*line_index) + 1] == '|')
		|| (line[*line_index] == '<' && line[(*line_index) + 1] == '<')
		|| (line[*line_index] == '>' && line[(*line_index) + 1] == '>'))
		return (1);
	return (0);
}

int	search_single_operator(char *line, int *line_index)
{
	if (line[*line_index] == '|' || line[*line_index] == '<'
		|| line[*line_index] == '>' || line[*line_index] == '('
		|| line[*line_index] == ')')
		return (1);
	return (0);
}

char	*copy_operator(char *line, int len, int *line_index)
{
	char	*token;
	int		i;

	i = 0;
	token = malloc(len + 1);
	while (i < len)
	{
		token[i] = line[(*line_index)++];
		i++;
	}
	token[i] = '\0';
	return (token);
}

char	*copy_word(char *line, int *line_index)
{
	char	*token;
	int		token_index;

	token_index = 0;
	token = malloc(4096);
	if (!token)
		return (NULL);
	while (line[*line_index] && !search_double_operator(line, line_index)
		&& !search_single_operator(line, line_index) && line[*line_index] != ' '
		&& line[*line_index] != '\t')
		token[token_index++] = line[(*line_index)++];
	token[token_index] = '\0';
	return (token);
}
