/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:55:42 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/07 14:39:15 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_camera_direction(t_scene *scene, char *line, int *i)
{
	scene->camera.direction = vector(parse_float(line, i),
			parse_float(line, i), parse_float(line, i));
}

void	set_camera_position(t_scene *scene, char *line, int *i)
{
	scene->camera.position = point(parse_float(line, i),
			parse_float(line, i), parse_float(line, i));
}

int	parser_error(const char *msg)
{
	size_t	len;

	if (!msg)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	len = ft_strlen(msg);
	write(2, "Error\n", 6);
	write(2, msg, len);
	if (len == 0 || msg[len - 1] != '\n')
		write(2, "\n", 1);
	return (0);
}

void	cleanup_scene_objects(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->object[i].shape)
		{
			free(scene->object[i].shape);
			scene->object[i].shape = NULL;
		}
		i++;
	}
	scene->object_count = 0;
	scene->has_ambient = false;
	scene->has_camera = false;
	scene->has_light = false;
}

int	check_object_limit(t_scene *scene)
{
	if (scene->object_count >= MAX_OBJECTS)
		return (parser_error("Too many objects"));
	return (1);
}
