/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:45:08 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:22 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/utils.h"
#include "../../includes/clean.h"

static char	*ft_get_single_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*complete_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(complete_path, X_OK) == 0)
			return (complete_path);
		free(complete_path);
		i++;
	}
	return (NULL);
}

char	*ft_get_cmd_path(char **envp, char *cmd)
{
	char	**paths;
	char	*env_path;
	char	*single_path;
	int		i;

	i = 0;
	env_path = NULL;
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	single_path = ft_get_single_path(paths, cmd);
	free_split(paths);
	return (single_path);
}
