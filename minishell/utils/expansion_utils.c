/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:09:56 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/09 01:37:49 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_home_expansion(char *token, int *i,
				char *buf, int buf_index);

int	copy_unquoted(char *token, int *i, char *buf, int buf_index)
{
	if (token[*i] == '$')
		buf_index = handle_var_expansion(token, i, buf, buf_index);
	else if (token[*i] == '~' && buf_index == 0 && (token[*i + 1] == '\0'
			|| token[*i + 1] == '/'))
		buf_index = handle_home_expansion(token, i, buf, buf_index);
	else
		buf[buf_index++] = token[(*i)++];
	return (buf_index);
}

char	*ft_get_env(const char *name)
{
	char	**envp;
	int		i;
	size_t	len;

	envp = copy_env(NULL);
	if (!envp || !name)
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (envp[i] && envp)
	{
		if (ft_strncmp(name, envp[i], len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

int	handle_var_expansion(char *token, int *i, char *buf, int buf_index)
{
	char	*var;

	var = expand_var(token, i);
	if (var)
	{
		ft_strcpy(buf + buf_index, var);
		buf_index += ft_strlen(var);
		free(var);
	}
	return (buf_index);
}

static int	handle_home_expansion(char *token, int *i, char *buf, int buf_index)
{
	char	*home;

	home = ft_get_env("HOME");
	if (home)
	{
		ft_strcpy(buf + buf_index, home);
		buf_index += ft_strlen(home);
		free(home);
	}
	else
		buf[buf_index] = '~';
	(*i)++;
	while (token[*i] && token[*i] != ' ' && token[*i] != '\t' )
		buf[buf_index++] = token[(*i)++];
	return (buf_index);
}
