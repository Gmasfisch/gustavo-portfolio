/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:36:09 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:36:10 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_intersection	create_intersection(float t, void *object)
{
	t_intersection	new_intersection;

	new_intersection.t = t;
	new_intersection.object = object;
	return (new_intersection);
}

t_intersections	intersections(int n, t_intersection arr[])
{
	t_intersections	xs;
	int				i;
	int				limit;

	if (n > MAX_INTERSECTIONS)
		n = MAX_INTERSECTIONS;
	xs.count = n;
	i = 0;
	limit = MAX_INTERSECTIONS;
	while (i < limit)
	{
		xs.data[i] = arr[i];
		i++;
	}
	return (xs);
}

//find smallest t value
t_intersection	*hit(t_intersections *intersections)
{
	t_intersection	*hit;
	int				i;

	i = 0;
	hit = NULL;
	while (i < intersections->count)
	{
		if (intersections->data[i].t > 0 && (hit == NULL
				|| intersections->data[i].t < hit->t))
			hit = &intersections->data[i];
		i++;
	}
	return (hit);
}

int	intersect_objects(t_scene *scene, t_ray ray, t_intersection *arr)
{
	int	count;
	int	i;
	int	added;

	count = 0;
	i = 0;
	while (i < scene->object_count && count < MAX_INTERSECTIONS)
	{
		added = object_intersections(&scene->object[i], ray, arr, count);
		if (added < 0)
			break ;
		count += added;
		if (count > MAX_INTERSECTIONS)
			count = MAX_INTERSECTIONS;
		i++;
	}
	return (count);
}

int	object_intersections(t_object *obj, t_ray ray,
		t_intersection *arr, int start)
{
	if (obj->type == SPHERE)
		return (sphere_intersections(obj, ray, arr, start));
	if (obj->type == CYLINDER)
		return (cylinder_intersections(obj, ray, arr, start));
	if (obj->type == PLANE)
		return (plane_intersections(obj, ray, arr, start));
	return (0);
}
