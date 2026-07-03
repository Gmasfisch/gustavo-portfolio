/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:30 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/07 14:22:54 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	sphere_intersections(t_object *obj, t_ray ray,
		t_intersection *arr, int start)
{
	t_tuple				sphere_to_ray;
	t_intersection_data	ldata;
	t_sphere			*sp;
	float				t0;
	float				t1;

	if (start >= MAX_INTERSECTIONS)
		return (0);
	sp = (t_sphere *) obj->shape;
	sphere_to_ray = sub_tuple(ray.origin, sp->center);
	sphere_to_ray = vector(sphere_to_ray.x, sphere_to_ray.y, sphere_to_ray.z);
	ldata.a = get_dot_product(ray.direction, ray.direction);
	ldata.b = 2.0f * get_dot_product(ray.direction, sphere_to_ray);
	ldata.c = get_dot_product(sphere_to_ray, sphere_to_ray)
		- sp->radius * sp->radius;
	ldata.discriminant = ldata.b * ldata.b - 4.0f * ldata.a * ldata.c;
	if (ldata.discriminant < 0)
		return (0);
	t0 = (-ldata.b - sqrtf(ldata.discriminant)) / (2.0f * ldata.a);
	t1 = (-ldata.b + sqrtf(ldata.discriminant)) / (2.0f * ldata.a);
	arr[start] = create_intersection(t0, obj);
	if (start + 1 >= MAX_INTERSECTIONS)
		return (1);
	arr[start + 1] = create_intersection(t1, obj);
	return (2);
}

t_tuple	sphere_normal(t_sphere *sphere, t_tuple intersection_point)
{
	t_tuple	v;

	v = sub_tuple(intersection_point, sphere->center);
	v = vector(v.x, v.y, v.z);
	return (normalize(v));
}
