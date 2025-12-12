/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:28:31 by gfischba          #+#    #+#             */
/*   Updated: 2025/12/12 09:33:17 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"

void	here_doc_mode(t_pipex *pipex, char **argv, int argc)
{
	int	pipefd[2];

	pipex->argv = argv;
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	read_heredoc_input(pipefd[1], argv[2]);
	close(pipefd[1]);
	pipex->infile_fd = pipefd[0];
	pipex->outfile_fd = open(argv[argc - 1], O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror ("outfile couldnt open");
		exit (EXIT_FAILURE);
	}
}

void	read_heredoc_input(int write_fd, const char *limiter)
{
	char	*line;

	while (1)
	{
		write(2, "heredoc>", 8);
		line = get_next_line(0);
		if (line == NULL)
		{
			perror("error reading from stdin");
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		else
		{
			write(write_fd, line, ft_strlen(line));
			free(line);
		}
	}
}
