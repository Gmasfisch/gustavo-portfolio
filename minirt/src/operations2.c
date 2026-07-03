/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:36:24 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 15:01:07 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	normalize(t_tuple tuple)
{
	float	magnitude;
	t_tuple	normalized_tuple;

	magnitude = get_magnitude(tuple);
	if (equal(magnitude, 0.0))
		return (tuple);
	normalized_tuple.x = tuple.x / magnitude;
	normalized_tuple.y = tuple.y / magnitude;
	normalized_tuple.z = tuple.z / magnitude;
	normalized_tuple.w = 0.0f;
	return (normalized_tuple);
}

t_tuple	negate(t_tuple tuple)
{
	t_tuple	negated_tuple;

	negated_tuple.x = -tuple.x;
	negated_tuple.y = -tuple.y;
	negated_tuple.z = -tuple.z;
	negated_tuple.w = tuple.w;
	return (negated_tuple);
}

t_tuple	scalar_multiplication(t_tuple vector, float scalar)
{
	t_tuple	multiplied_vector;

	multiplied_vector.x = vector.x * scalar;
	multiplied_vector.y = vector.y * scalar;
	multiplied_vector.z = vector.z * scalar;
	multiplied_vector.w = vector.w;
	return (multiplied_vector);
}

float	get_dot_product(t_tuple a, t_tuple b)
{
	float	dot_product;

	dot_product = a.x * b.x + a.y
		* b.y + a.z * b.z + a.w * b.w;
	return (dot_product);
}

t_tuple	get_cross_product(t_tuple a, t_tuple b)
{
	t_tuple	cross_tuple;

	cross_tuple.x = a.y * b.z - a.z * b.y;
	cross_tuple.y = a.z * b.x - a.x * b.z;
	cross_tuple.z = a.x * b.y - a.y * b.x;
	cross_tuple.w = 0.0f;
	return (cross_tuple);
}
