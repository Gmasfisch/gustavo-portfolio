/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:55:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:10 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

static size_t	export_key_len(const char *entry)
{
	size_t	i;

	i = 0;
	while (entry && entry[i] && entry[i] != '=')
		i++;
	return (i);
}

static int	export_find_index(char **env, const char *entry)
{
	size_t	key_len;
	size_t	i;

	if (!env || !entry)
		return (-1);
	key_len = export_key_len(entry);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], entry, key_len) == 0 && env[i][key_len] == '=')
			return ((int)i);
		i++;
	}
	return (-1);
}

static int	export_append_entry(char ***env, char *entry)
{
	char	**old;
	char	**new_env;
	size_t	count;
	size_t	i;

	old = *env;
	count = 0;
	while (old && old[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (free(entry), 1);
	i = 0;
	while (old && old[i])
	{
		new_env[i] = old[i];
		i++;
	}
	new_env[i] = entry;
	new_env[i + 1] = NULL;
	free(old);
	*env = new_env;
	copy_env(new_env);
	return (0);
}

int	export_store(char ***env, const char *assignment)
{
	char	*dup;
	int		index;

	if (!env || !assignment)
		return (1);
	dup = ft_strdup(assignment);
	if (!dup)
		return (1);
	index = export_find_index(*env, assignment);
	if (index >= 0)
	{
		free((*env)[index]);
		(*env)[index] = dup;
		return (0);
	}
	return (export_append_entry(env, dup));
}
