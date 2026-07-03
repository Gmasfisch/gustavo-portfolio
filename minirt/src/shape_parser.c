/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 21:53:02 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/07 14:31:30 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	parse_shape(t_scene *scene, char *line)
{
	int	res;

	res = 0;
	if (line[0] == 's' && line[1] == 'p'
		&& (line[2] == ' ' || line[2] == '\t'))
		res = parse_sphere(scene, line);
	else if (line[0] == 'p' && line[1] == 'l'
		&& (line[2] == ' ' || line[2] == '\t'))
		res = parse_plane(scene, line);
	else if (line[0] == 'c' && line[1] == 'y'
		&& (line[2] == ' ' || line[2] == '\t'))
		res = parse_cylinder(scene, line);
	if (res == 0)
		return (parser_error("Invalid shape formatting or unknown type"));
	return (1);
}

int	parse_sphere(t_scene *scene, char *line)
{
	t_sphere	*sp;
	int			i;
	t_color		color;

	i = 2;
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (0);
	trim_spaces(line, &i);
	sp->center.x = parse_float(line, &i);
	sp->center.y = parse_float(line, &i);
	sp->center.z = parse_float(line, &i);
	sp->radius = parse_float(line, &i) / 2;
	if (!set_color(line, &i, &color))
		return (free(sp), 0);
	set_default_material(scene, color, SPHERE, sp);
	scene->object_count++;
	return (1);
}

int	parse_cylinder(t_scene *scene, char *line)
{
	t_cylinder	*cylinder;
	int			i;
	t_color		color;

	i = 2;
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	trim_spaces(line, &i);
	cylinder->center = point(parse_float(line, &i),
			parse_float(line, &i), parse_float(line, &i));
	cylinder->axisv = vector(parse_float(line, &i),
			parse_float(line, &i), parse_float(line, &i));
	if (!check_axis_value(cylinder->axisv)
		|| equal(get_magnitude(cylinder->axisv), 0.0f))
		return (free(cylinder), 0);
	cylinder->axisv = normalize(cylinder->axisv);
	init_cylinder_rotation(cylinder);
	set_cylinder(line, &i, cylinder);
	if (!set_color(line, &i, &color))
		return (free(cylinder), 0);
	cylinder->closed = 1;
	set_default_material(scene, color, CYLINDER, cylinder);
	scene->object_count++;
	return (1);
}

int	parse_plane(t_scene *scene, char *line)
{
	t_plane	*pl;
	int		i;
	t_color	color;

	i = 2;
	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (0);
	trim_spaces(line, &i);
	set_plane(line, &i, pl);
	if (!check_axis_value(pl->normal) || equal(get_magnitude(pl->normal), 0.0f))
		return (free(pl), 0);
	pl->normal = normalize(pl->normal);
	if (!set_color(line, &i, &color))
		return (free(pl), 0);
	set_default_material(scene, color, PLANE, pl);
	scene->object_count++;
	return (1);
}

void	set_default_material(t_scene *scene, t_color color,
	t_object_type type, void *shape)
{
	int	obj_index;

	obj_index = scene->object_count;
	scene->object[obj_index].type = type;
	scene->object[obj_index].shape = shape;
	scene->object[obj_index].material.color = color;
	scene->object[obj_index].material.ambient = 0.1;
	scene->object[obj_index].material.diffuse = 0.7;
	scene->object[obj_index].material.specular = 0.3;
	scene->object[obj_index].material.shininess = 50;
}
