/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:14:26 by gfischba          #+#    #+#             */
/*   Updated: 2025/05/28 13:56:08 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_for_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**dir;
	char	*path;
	char	*envp_copy;
	int		i;

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	envp_copy = ft_strdup(path_env);
	if (!envp_copy)
		return (NULL);
	dir = ft_split(envp_copy, ':');
	i = 0;
	while (dir[i])
	{
		path = build_path(dir[i], cmd);
		if (path && access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path_env(char **envp)
{
	int		i;
	char	*path_env;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			return (path_env);
		}
		i++;
	}
	return (NULL);
}

char	*build_path(char *dir, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*path;	

	cmd_len = ft_strlen(cmd);
	path_len = ft_strlen(dir) + cmd_len + 2;
	path = malloc(path_len);
	if (!path)
		return (NULL);
	if (path)
	{
		ft_strlcpy(path, dir, path_len);
		ft_strlcat(path, "/", path_len);
		ft_strlcat(path, cmd, path_len);
	}
	return (path);
}

void	close_pipe(int *pipefd)
{
	if (pipefd[0] != -1) 
		close(pipefd[0]);
	if (pipefd[1] != -1) 
		close(pipefd[1]);
}

void	wait_all(void)
{
	int	status;

	while (wait(&status) > 0)
		;
}
