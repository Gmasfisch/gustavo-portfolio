/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:17:28 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:06 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	find_key_index(char **env, const char *key)
{
	size_t	k;
	int		i;

	if (!env || !key)
		return (-1);
	k = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, k) && env[i][k] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*make_env_entry(const char *key, const char *value)
{
	size_t	k;
	size_t	v;
	char	*entry;

	k = ft_strlen(key);
	if (value)
		v = ft_strlen(value);
	else
		v = 0;
	entry = malloc(k + 1 + v + 1);
	if (!entry)
		return (NULL);
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	if (value)
		ft_strcat(entry, value);
	return (entry);
}

static int	append_env_entry(char ***env, char *entry)
{
	char	**e;
	char	**tmp;
	int		n;

	e = *env;
	n = 0;
	while (e && e[n])
		n++;
	tmp = malloc(sizeof(char *) * (n + 2));
	if (!tmp)
		return (free(entry), 1);
	n = 0;
	while (e && e[n])
	{
		tmp[n] = e[n];
		n++;
	}
	tmp[n] = entry;
	tmp[n + 1] = NULL;
	free(e);
	copy_env(tmp);
	*env = tmp;
	return (0);
}

static int	update_env_var(char ***env, char *key, char *value)
{
	char	**e;
	char	*entry;
	int		idx;

	if (!env || !key)
		return (1);
	e = *env;
	entry = make_env_entry(key, value);
	if (!entry)
		return (1);
	idx = find_key_index(e, key);
	if (idx >= 0)
	{
		free(e[idx]);
		e[idx] = entry;
		return (0);
	}
	return (append_env_entry(env, entry));
}

int	builtin_cd(char **args, char ***env)
{
	char	*target_dir;
	char	*oldpwd_dup;
	char	*new_pwd;

	target_dir = get_target_dir(args);
	if (target_dir == NULL)
		return (1);
	oldpwd_dup = dup_oldpwd();
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		free(oldpwd_dup);
		free(target_dir);
		return (1);
	}
	new_pwd = get_newpwd(target_dir);
	update_env_var(env, "OLDPWD", oldpwd_dup);
	update_env_var(env, "PWD", new_pwd);
	print_if_dash(args, new_pwd);
	free(oldpwd_dup);
	free(new_pwd);
	free(target_dir);
	return (0);
}
