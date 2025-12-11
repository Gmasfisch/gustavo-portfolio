/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:19:31 by gfischba          #+#    #+#             */
/*   Updated: 2025/06/16 11:29:10 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_pipex *pipex, int i)
{
	char	*path;
	char	*cmd;

	if (pipex->here_doc == 0)
		cmd = pipex->argv[i + 2];
	else
		cmd = pipex->argv[i + 3];
	pipex->cmd_args = parser(cmd);
	if (!pipex->cmd_args || !pipex->cmd_args[0])
	{
		perror("Invalid command");
		exit(1);
	}
	path = search_for_path(pipex->cmd_args[0], pipex->envp);
	if (!path)
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	execve(path, pipex->cmd_args, pipex->envp);
	perror("execve failed");
	exit(1);
}

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	initialize_variables(t_pipex *pipex)
{
	pipex->cmd_args = NULL;
	pipex->cmds = NULL;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
}
