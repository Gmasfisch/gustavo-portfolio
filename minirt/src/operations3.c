/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:39 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/07 14:26:58 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	add_tuples(t_tuple a, t_tuple b)
{
	t_tuple	new_tuple;

	new_tuple.x = a.x + b.x;
	new_tuple.y = a.y + b.y;
	new_tuple.z = a.z + b.z;
	new_tuple.w = a.w + b.w;
	return (new_tuple);
}

t_tuple	sub_tuple(t_tuple a, t_tuple b)
{
	t_tuple	new_tuple;

	new_tuple.x = a.x - b.x;
	new_tuple.y = a.y - b.y;
	new_tuple.z = a.z - b.z;
	new_tuple.w = a.w - b.w;
	return (new_tuple);
}

float	get_magnitude(t_tuple vector)
{
	return (sqrtf(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z));
}
