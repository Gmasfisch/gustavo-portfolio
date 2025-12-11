/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:00:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/13 20:00:00 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**dup_token_array(char **args, int count)
{
	char	**dup;
	int		i;

	dup = malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(args[i]);
		if (!dup[i])
		{
			while (i > 0)
				free(dup[--i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[count] = NULL;
	return (dup);
}

char	**expand_tokens(char **args)
{
	char	**dup;
	int		count;

	if (!args)
		return (NULL);
	count = count_tokens(args);
	dup = dup_token_array(args, count);
	if (!dup)
		return (NULL);
	return (expansion(dup));
}

char	*expand_word(const char *token)
{
	char	*tmp[2];
	char	**expanded;
	char	*result;

	if (!token)
		return (NULL);
	tmp[0] = (char *)token;
	tmp[1] = NULL;
	expanded = expand_tokens(tmp);
	if (!expanded)
		return (NULL);
	if (!expanded[0])
	{
		free_split(expanded);
		return (ft_strdup(""));
	}
	result = ft_strdup(expanded[0]);
	free_split(expanded);
	return (result);
}
