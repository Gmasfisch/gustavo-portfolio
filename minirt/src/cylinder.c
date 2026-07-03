/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:20:31 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/06 00:52:37 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	check_y(t_object *obj, t_intersection_data *ldata,
			t_intersection *arr, int start)
{
	float		y;
	float		h2;
	int			n;
	t_cylinder	*cy;

	if (start >= MAX_INTERSECTIONS)
		return (0);
	cy = (t_cylinder *) obj->shape;
	h2 = cy->height / 2.0f;
	n = 0;
	y = ldata->local_ray.origin.y + ldata->t[0] * ldata->local_ray.direction.y;
	if (y > -h2 && y < h2)
	{
		if (start + n >= MAX_INTERSECTIONS)
			return (n);
		arr[start + n++] = create_intersection(ldata->t[0], obj);
	}
	y = ldata->local_ray.origin.y + ldata->t[1] * ldata->local_ray.direction.y;
	if (y > -h2 && y < h2)
	{
		if (start + n >= MAX_INTERSECTIONS)
			return (n);
		arr[start + n++] = create_intersection(ldata->t[1], obj);
	}
	return (n);
}

int	cylinder_intersections(t_object *obj, t_ray ray,
		t_intersection *arr, int start)
{
	t_intersection_data	ldata;
	t_cylinder			*cy;
	int					n;

	cy = (t_cylinder *)obj->shape;
	ldata.local_ray = transform_ray_to_local(cy, ray);
	solve_quadratic(&ldata, cy);
	if (fabs(ldata.a) < EPSILON)
	{
		if (cy->closed)
			return (check_cap(obj, ldata.local_ray, arr, start));
		return (0);
	}
	ldata.discriminant = powf(ldata.b, 2) - 4 * ldata.a * ldata.c;
	if (ldata.discriminant < 0)
		return (0);
	get_t_values(ldata.a, ldata.b, ldata.discriminant, ldata.t);
	n = check_y(obj, &ldata, arr, start);
	if (cy->closed)
		n += check_cap(obj, ldata.local_ray, arr, start + n);
	return (n);
}

int	check_cap(t_object *obj, t_ray ray, t_intersection *arr, int start)
{
	t_cylinder	*cy;
	float		h2;
	float		tcap;
	int			n;

	cy = NULL;
	h2 = 0.0f;
	tcap = 0.0f;
	n = 0;
	if (start >= MAX_INTERSECTIONS)
		return (0);
	if (fabsf(ray.direction.y) < EPSILON)
		return (0);
	cy = (t_cylinder *)obj->shape;
	h2 = cy->height / 2.0f;
	tcap = (h2 - ray.origin.y) / ray.direction.y;
	if (cap_hit(cy, ray, tcap) && start + n < MAX_INTERSECTIONS)
		arr[start + n++] = create_intersection(tcap, obj);
	tcap = (-h2 - ray.origin.y) / ray.direction.y;
	if (cap_hit(cy, ray, tcap) && start + n < MAX_INTERSECTIONS)
		arr[start + n++] = create_intersection(tcap, obj);
	return (n);
}

t_tuple	cylinder_normal(t_object *obj, t_tuple intersection_point)
{
	t_cylinder	*cy;
	t_tuple		local_p;
	t_tuple		local_normal;
	t_tuple		world_normal;
	float		h2;

	cy = (t_cylinder *) obj->shape;
	h2 = cy->height / 2.0f;
	local_p = sub_tuple(intersection_point, cy->center);
	local_p = multiply_matrix_tuple(cy->rotation_matrix, local_p);
	if (cy->closed && local_p.y >= h2 - EPSILON)
		local_normal = vector(0, 1, 0);
	else if (cy->closed && local_p.y <= -h2 + EPSILON)
		local_normal = vector(0, -1, 0);
	else
		local_normal = vector(local_p.x, 0, local_p.z);
	local_normal.w = 0;
	world_normal = multiply_matrix_tuple(transpose_matrix
			(cy->rotation_matrix), local_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

void	get_t_values(float a, float b, float discriminant, float t[2])
{
	t[0] = (-b - sqrtf(discriminant)) / (2.0f * a);
	t[1] = (-b + sqrtf(discriminant)) / (2.0f * a);
}
