/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:35:50 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:35:51 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	solve_quadratic(t_intersection_data *ldata, t_cylinder *cy)
{
	ldata->a = powf(ldata->local_ray.direction.x, 2)
		+ powf(ldata->local_ray.direction.z, 2);
	ldata->b = 2 * (ldata->local_ray.origin.x * ldata->local_ray.direction.x
			+ ldata->local_ray.origin.z * ldata->local_ray.direction.z);
	ldata->c = powf(ldata->local_ray.origin.x, 2)
		+ powf(ldata->local_ray.origin.z, 2) - powf(cy->radius, 2);
}

t_ray	transform_ray_to_local(t_cylinder *cy, t_ray ray)
{
	t_ray	local;

	local.origin = sub_tuple(ray.origin, cy->center);
	local.direction = ray.direction;
	cylinder_rotation(cy, &local.direction, &local.origin);
	return (local);
}

int	cap_hit(t_cylinder *cy, t_ray ray, float tcap)
{
	float	x;
	float	z;

	x = ray.origin.x + tcap * ray.direction.x;
	z = ray.origin.z + tcap * ray.direction.z;
	if ((x * x) + (z * z) <= (cy->radius * cy->radius) + EPSILON)
		return (1);
	return (0);
}
