/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:00:44 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:36:20 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool	is_vector(t_tuple tuple)
{
	return (fabsf(tuple.w - 0.0f) < EPSILON);
}

bool	is_point(t_tuple tuple)
{
	return (fabsf(tuple.w - 1.0f) < EPSILON);
}

t_tuple	point(float x, float y, float z)
{
	const t_tuple	new_point = {.x = x, .y = y, .z = z, .w = 1.0f};

	return (new_point);
}

t_tuple	vector(float x, float y, float z)
{
	const t_tuple	new_vector = {.x = x, .y = y, .z = z, .w = 0.0f};

	return (new_vector);
}

bool	equal(float a, float b)
{
	if (fabsf(a - b) < EPSILON)
		return (true);
	return (false);
}
