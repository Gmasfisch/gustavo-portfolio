/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:45:08 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:04 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return (NULL);
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*get_target_dir(char **args)
{
	char	*home;
	char	*oldpwd;

	if (!args[1] || args[1][0] == '\0')
	{
		home = ft_get_env("HOME");
		if (!home)
		{
			write(2, "cd: HOME not set\n", 17);
			return (NULL);
		}
		return (ft_strdup(home));
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		oldpwd = ft_get_env("OLDPWD");
		if (!oldpwd)
		{
			write(2, "cd: OLDPWD not set\n", 19);
			return (NULL);
		}
		return (ft_strdup(oldpwd));
	}
	return (ft_strdup(args[1]));
}

int	is_builtin_cmd_node(t_node *n)
{
	char	**expanded;
	int		result;

	if (!n || n->type != NODE_COMMAND || !n->cmd_args)
		return (0);
	expanded = expand_tokens(n->cmd_args);
	if (!expanded)
		return (0);
	result = (expanded[0] && is_builtin(expanded[0]));
	free_split(expanded);
	return (result);
}
