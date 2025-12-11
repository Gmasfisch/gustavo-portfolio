/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 01:14:50 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/03 18:26:50 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_var(char *token, int *i)
{
	char	name[128];
	int		j;
	char	*value;

	j = 0;
	if (token[*i + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(get_shell_status()));
	}
	(*i)++;
	while (ft_isalnum(token[*i]) || token[*i] == '_')
		name[j++] = token[(*i)++];
	name[j] = '\0';
	value = ft_get_env(name);
	if (value)
		return (value);
	return (NULL);
}
