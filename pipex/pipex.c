/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:25:53 by gfischba          #+#    #+#             */
/*   Updated: 2025/12/12 09:47:19 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
	{
		perror("malloc failure");
		return (NULL);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->here_doc = 1;
	else
		pipex->here_doc = 0;
	pipex->cmd_count = count_cmds(argc, pipex->here_doc);
	pipex->envp = envp;
	pipex->argv = argv;
	initialize_variables(pipex);
	return (pipex);
}

void	normal_mode(t_pipex *pipex, char **argv, int argc)
{
	pipex->infile_fd = open(argv[1], O_RDONLY, O_CREAT);
	if (pipex->infile_fd == -1)
	{
		perror("opening file failure");
		exit(EXIT_FAILURE);
	}
	pipex->outfile_fd = open(argv[argc - 1], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("opening file failure");
		exit(EXIT_FAILURE);
	}
}

void	pipe_loop(t_pipex *pipex, int *prev_pipe, int *curr_pipe, int i)
{
	if (i == 0)
	{
		if (dup2(pipex->infile_fd, STDIN_FILENO) < 0)
		{
			perror("dup 2 failed");
			close(pipex->infile_fd);
		}
	}
	else
		if (dup2(prev_pipe[0], STDIN_FILENO) < 0)
			perror("dup2 prev_pipe[0] failed");
	if (i == pipex->cmd_count - 1)
	{
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile failed");
			close(pipex->outfile_fd);
		}
	}
	else
		if (dup2(curr_pipe[1], STDOUT_FILENO) < 0)
			perror("dup2 curr_pipe");
	close_pipe(prev_pipe);
	close_pipe(curr_pipe);
	execute_command(pipex, i);
}

void	create_pipes(t_pipex *pipex,
				int *prev_pipe, int *curr_pipe, int i)
{
	pid_t	pid;

	pid = fork();
	check_fork_error(pid);
	if (pid == 0)
		pipe_loop(pipex, prev_pipe, curr_pipe, i);
	else
		close_pipe(prev_pipe);
}

void	execute_pipeline(t_pipex *pipex)
{
	int		prev_pipe[2];
	int		curr_pipe[2];
	int		i;

	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	i = 0;
	while (i < pipex->cmd_count)
	{
		if (i < pipex->cmd_count - 1)
		{
			if (pipe(curr_pipe) == -1)
			{
				perror("pipe failed");
				exit(EXIT_FAILURE);
			}
		}
		create_pipes(pipex, prev_pipe, curr_pipe, i);
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
		i++;
	}
	wait_all();
}
