/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:35 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/06 00:54:35 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cylinder_rotation(t_cylinder *cy)
{
	t_tuple	rotation_axis;
	float	angle;
	float	dot;

	cy->axisv = normalize(cy->axisv);
	dot = get_dot_product(cy->axisv, vector(0, 1, 0));
	if (dot > 0.99999f || dot < -0.99999f)
	{
		cy->rotation_matrix = identity_matrix();
		return ;
	}
	rotation_axis = normalize(get_cross_product(cy->axisv, vector(0, 1, 0)));
	angle = acosf(dot);
	cy->rotation_matrix = compute_rotation_matrix(rotation_axis, angle);
}

void	cylinder_rotation(t_cylinder *cy,
		t_tuple *ray_direction, t_tuple *cy_ray)
{
	*cy_ray = multiply_matrix_tuple(cy->rotation_matrix, *cy_ray);
	*ray_direction = multiply_matrix_tuple(cy->rotation_matrix, *ray_direction);
	cy_ray->w = 1.0f;
	ray_direction->w = 0.0f;
}

t_matrix	compute_rotation_matrix(t_tuple ra, float an)
{
	float		a;
	float		b;
	float		c;
	t_matrix	rm;

	a = cosf(an);
	b = sinf(an);
	c = 1 - a;
	rm.m[0][0] = c * ra.x * ra.x + a;
	rm.m[0][1] = c * ra.x * ra.y - b * ra.z;
	rm.m[0][2] = c * ra.x * ra.z + b * ra.y;
	rm.m[1][0] = c * ra.x * ra.y + b * ra.z;
	rm.m[1][1] = c * ra.y * ra.y + a;
	rm.m[1][2] = c * ra.y * ra.z - b * ra.x;
	rm.m[2][0] = c * ra.x * ra.z - b * ra.y;
	rm.m[2][1] = c * ra.y * ra.z + b * ra.x;
	rm.m[2][2] = c * ra.z * ra.z + a;
	return (rm);
}

t_tuple	multiply_matrix_tuple(t_matrix m, t_tuple v)
{
	t_tuple	new;

	new.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	new.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	new.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
	new.w = v.w;
	return (new);
}

t_matrix	transpose_matrix(t_matrix m)
{
	t_matrix	t;

	t.m[0][0] = m.m[0][0];
	t.m[0][1] = m.m[1][0];
	t.m[0][2] = m.m[2][0];
	t.m[1][0] = m.m[0][1];
	t.m[1][1] = m.m[1][1];
	t.m[1][2] = m.m[2][1];
	t.m[2][0] = m.m[0][2];
	t.m[2][1] = m.m[1][2];
	t.m[2][2] = m.m[2][2];
	return (t);
}
