/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:30:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/13 19:30:00 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(char **envp)
{
	static char	**g_env = NULL;

	if (envp != NULL)
		g_env = envp;
	return (g_env);
}

char	**dup_env(char **envp)
{
	char	**copy;
	size_t	count;
	size_t	i;

	count = 0;
	while (envp && envp[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

size_t	env_count(char **env)
{
	size_t	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}

char	*env_entry_dup(const char *key, const char *value, size_t *key_len)
{
	char	*entry;
	size_t	value_len;

	if (!key || !*key)
		return (NULL);
	*key_len = ft_strlen(key);
	if (!value)
		value = "";
	value_len = ft_strlen(value);
	entry = malloc(*key_len + value_len + 2);
	if (!entry)
		return (NULL);
	ft_memcpy(entry, key, *key_len);
	entry[*key_len] = '=';
	ft_memcpy(entry + *key_len + 1, value, value_len);
	entry[*key_len + 1 + value_len] = '\0';
	return (entry);
}
