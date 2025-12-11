/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:06:14 by mlemoula          #+#    #+#             */
/*   Updated: 2025/09/24 11:29:07 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	free_split(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	free (paths);
}

void	free_ast(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd_args)
		free_split(node->cmd_args);
	if (node->filename)
		free(node->filename);
	free(node);
}
