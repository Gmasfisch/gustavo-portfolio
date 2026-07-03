/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:19:49 by mlemoula          #+#    #+#             */
/*   Updated: 2026/07/03 15:56:46 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = normalize(direction);
	return (new_ray);
}

t_tuple	position(t_ray *ray, float t)
{
	return (add_tuples(ray->origin, scalar_multiplication(ray->direction, t)));
}

t_ray	get_ray_for_pixel(t_camera camera, int px, int py)
{
	t_ray			ray;
	t_camera_data	cdata;
	t_tuple			dir;

	setup_camera(&camera);
	cdata.aspect = (float)WIDTH / (float)HEIGHT;
	cdata.half_view = tanf((camera.fov * 0.5f) * (float)M_PI / 180.0f);
	cdata.world_x = (2.0f * ((float)px + 0.5f) / (float)WIDTH - 1.0f)
		* cdata.half_view * cdata.aspect;
	cdata.world_y = (1.0f - 2.0f * ((float)py + 0.5f) / (float)HEIGHT)
		* cdata.half_view;
	dir = add_tuples(camera.forward,
			add_tuples(scalar_multiplication(camera.right, cdata.world_x),
				scalar_multiplication(camera.up, -cdata.world_y)));
	ray.origin = camera.position;
	ray.direction = normalize(dir);
	return (ray);
}

void	setup_camera(t_camera *camera)
{
	t_tuple	up_guide;

	camera->forward = normalize(camera->direction);
	if (fabs(camera->forward.y) > 0.9f)
		up_guide = vector(0, 0, 1);
	else
		up_guide = vector(0, 1, 0);
	camera->right = normalize(get_cross_product(up_guide, camera->forward));
	camera->up = normalize(get_cross_product(camera->right, camera->forward));
}
