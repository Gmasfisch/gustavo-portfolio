/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:55:19 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/06 00:55:31 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_color(t_color color)
{
	float	r;
	float	g;
	float	b;

	r = color.r;
	g = color.g;
	b = color.b;
	if ((r <= 1 && r >= 0) && (g <= 1 && g >= 0) && (b <= 1 && b >= 0))
		return (1);
	return (0);
}
