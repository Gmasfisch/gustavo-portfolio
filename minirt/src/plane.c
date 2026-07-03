/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:11:30 by mlemoula          #+#    #+#             */
/*   Updated: 2026/01/28 10:45:29 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	plane_intersections(t_object *obj, t_ray ray,
		t_intersection *arr, int start)
{
	t_plane	*pl;
	float	denom;
	float	t;
	t_tuple	p0_to_origin;

	pl = (t_plane *)obj->shape;
	denom = get_dot_product(ray.direction, pl->normal);
	if (fabsf(denom) < EPSILON)
		return (0);
	p0_to_origin = sub_tuple(pl->point, ray.origin);
	t = get_dot_product(p0_to_origin, pl->normal) / denom;
	if (t > EPSILON)
	{
		arr[start] = create_intersection(t, obj);
		return (1);
	}
	return (0);
}
