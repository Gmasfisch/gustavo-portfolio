/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:50:12 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/05 19:50:13 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_matrix	identity_matrix(void)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			m.m[i][j] = (i == j);
			j++;
		}
		i++;
	}
	return (m);
}
