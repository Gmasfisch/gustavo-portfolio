/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:50:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:17 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	exec_and(t_node *left, t_node *right)
{
	int	status_left;

	status_left = execute_node(left);
	if (status_left == 130)
		return (status_left);
	if (status_left == 0)
		return (execute_node(right));
	return (status_left);
}

int	exec_or(t_node *left, t_node *right)
{
	int	status_left;

	status_left = execute_node(left);
	if (status_left == 130)
		return (status_left);
	if (status_left != 0)
		return (execute_node(right));
	return (status_left);
}
