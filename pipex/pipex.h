/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:55:16 by gfischba          #+#    #+#             */
/*   Updated: 2025/06/27 16:49:44 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../Libft/libft.h"

typedef struct s_pipex
{
	int		here_doc;
	int		infile_fd;
	int		outfile_fd;
	int		cmd_count;
	char	**cmds;
	char	**envp;
	char	**cmd_args;
	char	**argv;
}t_pipex;

//main
int		main(int argc, char **argv, char **envp);

//pipex.c
t_pipex	*init_pipex(int argc, char **argv, char **envp);
void	normal_mode(t_pipex *pipe, char **argv, int argc);
void	pipe_loop(t_pipex *pipex, int *prev_pipe, int *curr_pipe, int i);
void	create_pipes(t_pipex *pipex,
			int *prev_pipe, int *curr_pipe, int i);
void	execute_pipeline(t_pipex *pipex);

//execute.c
void	exit_error(char *msg);
void	execute_command(t_pipex *pipex, int i);
void	initialize_variables(t_pipex *pipex);

//utils.c
int		count_cmds(int argc, int here_doc);
void	check_fork_error(int pid);
void	free_pipex(t_pipex *pipex);

//path.c
char	*search_for_path(char *cmd, char **envp);
char	*get_path_env(char **envp);
char	*build_path(char *dir, char *cmd);
void	close_pipe(int *pipefd);
void	wait_all(void);

//parser
char	**parser(const char *cmd);

//bonus
void	here_doc_mode(t_pipex *pipex, char **argv, int argc);
void	read_heredoc_input(int write_fd, const char *limiter);

#endif