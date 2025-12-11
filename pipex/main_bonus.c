/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:43:05 by gfischba          #+#    #+#             */
/*   Updated: 2025/06/27 16:10:56 by gfischba         ###   ########.fr       */
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
	here_doc_mode(pipex, argv, argc);
	execute_pipeline(pipex);
	free_pipex(pipex);
	return (EXIT_SUCCESS);
}
