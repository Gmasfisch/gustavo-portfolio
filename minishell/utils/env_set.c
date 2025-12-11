/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:45:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 01:06:47 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	env_replace_existing(char **env, char *entry,
		const char *key, size_t key_len)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			free(env[i]);
			env[i] = entry;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	env_init_single(char ***env_ptr, char *entry)
{
	char	**env;

	env = malloc(sizeof(char *) * 2);
	if (!env)
		return (free(entry), 1);
	env[0] = entry;
	env[1] = NULL;
	*env_ptr = env;
	return (0);
}

static int	env_append_entry(char ***env_ptr, char *entry)
{
	char	**env;
	char	**new_env;
	size_t	i;
	size_t	count;

	env = *env_ptr;
	if (!env)
		return (env_init_single(env_ptr, entry));
	count = env_count(env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (free(entry), 1);
	i = 0;
	while (i < count)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[count] = entry;
	new_env[count + 1] = NULL;
	free(env);
	*env_ptr = new_env;
	return (0);
}

static int	env_insert(char ***env_ptr, char *entry,
		const char *key, size_t key_len)
{
	char	**env;

	env = *env_ptr;
	if (env_replace_existing(env, entry, key, key_len))
		return (0);
	return (env_append_entry(env_ptr, entry));
}

int	env_set(const char *key, const char *value)
{
	char	**env;
	char	*entry;
	size_t	key_len;

	entry = env_entry_dup(key, value, &key_len);
	if (!entry)
		return (1);
	env = copy_env(NULL);
	if (env_insert(&env, entry, key, key_len))
		return (1);
	copy_env(env);
	return (0);
}
