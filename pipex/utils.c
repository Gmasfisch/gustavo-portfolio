/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:22:19 by gfischba          #+#    #+#             */
/*   Updated: 2025/06/27 16:46:08 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_cmds(int argc, int here_doc)
{
	int	count;
	int	i;
	int	flag;

	count = 0;
	flag = here_doc;
	if (flag == 1)
		count = argc - 4;
	else if (flag == 0)
	{
		i = 2;
		while (i < argc - 1)
		{
			count ++;
			i++;
		}
	}
	return (count);
}

void	check_fork_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	if (pipex->cmd_args)
	{
		i = 0;
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
	free(pipex);
}
