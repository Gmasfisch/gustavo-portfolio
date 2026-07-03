/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:02 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/07 14:58:31 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	color_black(void)
{
	t_color	c;

	c.r = 0.0f;
	c.g = 0.0f;
	c.b = 0.0f;
	return (c);
}

t_color	compute_ambient(t_material m, t_ambient a)
{
	t_color	c;

	c = multiply_colors(m.color, a.color);
	c = color_scalar_mult(c, a.ratio * m.ambient);
	return (c);
}

t_color	compute_diffuse(t_material m, t_light l, float dot)
{
	t_color	c;

	c = multiply_colors(m.color, l.color);
	c = color_scalar_mult(c, m.diffuse * dot * l.brightness);
	return (c);
}

t_color	compute_specular(t_material m, t_light l,
		t_tuple reflectv, t_tuple eyev)
{
	float	f;
	float	reflect_dot_eye;
	t_color	c;

	reflect_dot_eye = get_dot_product(reflectv, eyev);
	if (reflect_dot_eye <= 0)
		return (color_black());
	if (reflect_dot_eye > 1.0f)
		reflect_dot_eye = 1.0f;
	f = powf(reflect_dot_eye, m.shininess);
	c = color_scalar_mult(l.color, m.specular * f * l.brightness);
	return (c);
}

t_tuple	normal_at(t_object *obj, t_tuple point)
{
	if (obj->type == SPHERE)
		return (sphere_normal((t_sphere *) obj->shape, point));
	else if (obj->type == CYLINDER)
		return (cylinder_normal(obj, point));
	else if (obj->type == PLANE)
		return (normalize(((t_plane *)obj->shape)->normal));
	return (vector(0, 0, 0));
}
