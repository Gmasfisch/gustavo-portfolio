/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:24:43 by gfischba          #+#    #+#             */
/*   Updated: 2025/06/16 11:46:08 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5)
		return (-1);
	pipex = init_pipex(argc, argv, envp);
	if (!pipex)
		return (EXIT_FAILURE);
	normal_mode(pipex, argv, argc);
	execute_pipeline(pipex);
	free_pipex(pipex);
	return (EXIT_SUCCESS);
}
