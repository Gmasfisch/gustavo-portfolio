/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:14:57 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:12 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

int	find_variable(char **env, char *key, int key_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_and_shift(char ***env, int index)
{
	int	j;

	j = index;
	free((*env)[j]);
	while ((*env)[j])
	{
		(*env)[j] = (*env)[j + 1];
		j++;
	}
}

static int	remove_env_var(char ***env, char *key)
{
	int		i;
	int		key_len;

	i = 0;
	key_len = ft_strlen(key);
	i = find_variable(*env, key, key_len);
	if (i == -1)
		return (0);
	remove_and_shift(env, i);
	return (0);
}

int	builtin_unset(char **args)
{
	int		i;
	char	**envp;

	envp = copy_env(NULL);
	i = 1;
	while (args[i])
	{
		remove_env_var(&envp, args[i]);
		i++;
	}
	return (0);
}
