/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:43:05 by gfischba          #+#    #+#             */
/*   Updated: 2025/12/12 09:33:42 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 6)
		return (-1);
	pipex = init_pipex(argc, argv, envp);
	if (!pipex)
		return (EXIT_FAILURE);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc_mode(pipex, argv, argc);
	else
		normal_mode(pipex, argv, argc);
	execute_pipeline(pipex);
	free_pipex(pipex);
	return (EXIT_SUCCESS);
}
