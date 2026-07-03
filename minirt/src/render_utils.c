/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:36:41 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:36:42 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_pixel_data(t_scene *scene, int x, int y, t_render_data *data)
{
	data->ray = get_ray_for_pixel(scene->camera, x, y);
	data->count = intersect_objects(scene, data->ray, data->arr);
	if (data->count <= 0)
		return (0);
	data->xs = intersections(data->count, data->arr);
	data->closest = hit(&data->xs);
	if (!data->closest)
		return (0);
	return (1);
}

void	shade_pixel(t_scene *scene, t_render_data *data)
{
	data->world_point = position(&data->ray, data->closest->t);
	data->normal = normal_at(data->closest->object, data->world_point);
	if (get_dot_product(data->normal, data->ray.direction) > 0)
		data->normal = negate(data->normal);
	set_light(scene, data);
	data->shadow = is_shadowed(scene, data->lgt.point, data->normal);
}
