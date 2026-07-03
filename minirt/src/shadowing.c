/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadowing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:58:34 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/06 01:01:18 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_shadow_hit(t_scene *scene, t_ray sray, float distance)
{
	t_intersection	arr[MAX_INTERSECTIONS];
	t_intersections	xs;
	t_intersection	*h;
	int				count;

	ft_bzero(arr, sizeof(arr));
	count = intersect_objects(scene, sray, arr);
	if (count <= 0)
		return (0);
	xs = intersections(count, arr);
	h = hit(&xs);
	if (h && h->t > 0.0001f && h->t < distance)
		return (1);
	return (0);
}

static t_ray	get_shadow_ray(t_light light, t_tuple point,
					t_tuple normal, float *dist)
{
	t_ray	ray;
	t_tuple	v_light;

	v_light = sub_tuple(light.position, point);
	*dist = get_magnitude(v_light);
	ray.origin = add_tuples(point, scalar_multiplication(normal, 0.001f));
	ray.direction = normalize(v_light);
	return (ray);
}

int	is_shadowed(t_scene *scene, t_tuple point, t_tuple normal)
{
	t_ray	sray;
	float	distance;

	sray = get_shadow_ray(scene->light, point, normal, &distance);
	return (is_shadow_hit(scene, sray, distance));
}
