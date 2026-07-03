/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:36:12 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 15:02:43 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	t_tuple	reflected;
	float	dot;

	reflected = vector(0.0, 0.0, 0.0);
	dot = get_dot_product(in, normal);
	reflected = scalar_multiplication(normal, 2 * dot);
	reflected = sub_tuple (in, reflected);
	return (reflected);
}

t_color	clamp_color(t_color c)
{
	if (c.r > 1.0f)
		c.r = 1.0f;
	if (c.g > 1.0f)
		c.g = 1.0f;
	if (c.b > 1.0f)
		c.b = 1.0f;
	if (c.r < 0.0f)
		c.r = 0.0f;
	if (c.g < 0.0f)
		c.g = 0.0f;
	if (c.b < 0.0f)
		c.b = 0.0f;
	return (c);
}

t_color	lighting(t_lighting lighting, int in_shadow)
{
	t_tuple			lightv;
	t_tuple			reflectv;
	float			light_dot;
	t_light_color	c;

	c.ambient = compute_ambient(lighting.material, lighting.ambient);
	if (in_shadow)
		return (c.ambient);
	lightv = normalize(sub_tuple(lighting.light.position, lighting.point));
	light_dot = get_dot_product(lightv, lighting.normalv);
	if (light_dot < 0)
	{
		c.diffuse = color_black();
		c.specular = color_black();
	}
	else
	{
		c.diffuse = compute_diffuse(lighting.material,
				lighting.light, light_dot);
		reflectv = reflect(negate(lightv), lighting.normalv);
		c.specular = compute_specular(lighting.material,
				lighting.light, reflectv, lighting.eyev);
	}
	return (clamp_color(add_colors(add_colors
				(c.ambient, c.diffuse), c.specular)));
}

void	set_light(t_scene *scene, t_render_data *data)
{
	data->lgt.material = data->closest->object->material;
	data->lgt.light = scene->light;
	data->lgt.ambient = scene->ambient;
	data->lgt.point = data->world_point;
	data->lgt.eyev = negate(data->ray.direction);
	data->lgt.normalv = data->normal;
}
