/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:19:09 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/06 00:19:11 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	get_file_data(char **argv, t_scene *scene)
{
	int		filefd;
	char	*line;

	filefd = open(argv[1], O_RDONLY);
	if (filefd == -1)
		return (parser_error("Could not open file"));
	scene->object_count = 0;
	line = get_next_line(filefd);
	while (line != NULL)
	{
		if (line[0] != '\0' && line[0] != '\n' && line[0] != '#')
		{
			if (!parse_line(scene, line))
			{
				free(line);
				close(filefd);
				cleanup_scene_objects(scene);
				return (0);
			}
		}
		free(line);
		line = get_next_line(filefd);
	}
	return (close(filefd), 1);
}

int	parse_line(t_scene *scene, char *line)
{
	if (!line || !line[1])
		return (0);
	if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_ambient(scene, line));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_camera(scene, line));
	if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_light(scene, line));
	if ((line[0] == 's' && line[1] == 'p')
		|| (line[0] == 'p' && line[1] == 'l')
		|| (line[0] == 'c' && line[1] == 'y'))
	{
		if (!check_object_limit(scene))
			return (0);
		return (parse_shape(scene, line));
	}
	return (parser_error("Unknown element identifier"));
}

int	parse_light(t_scene *scene, char *line)
{
	int	i;

	if (scene->has_light)
		return (parser_error("Light already defined"));
	i = 1;
	trim_spaces(line, &i);
	scene->light.position.x = parse_float(line, &i);
	scene->light.position.y = parse_float(line, &i);
	scene->light.position.z = parse_float(line, &i);
	scene->light.brightness = parse_float(line, &i);
	if (scene->light.brightness < 0.0f || scene->light.brightness > 1.0f)
		return (parser_error("Light brightness must be in the range [0,1]"));
	scene->light.color.r = (float) parse_int(line, &i) / 255.0f;
	scene->light.color.g = (float) parse_int(line, &i) / 255.0f;
	scene->light.color.b = (float) parse_int(line, &i) / 255.0f;
	if (!check_color(scene->light.color))
		return (parser_error("Light color must be between 0 and 255"));
	scene->has_light = true;
	return (1);
}

int	parse_camera(t_scene *scene, char *line)
{
	int		i;
	float	fov;

	if (scene->has_camera)
		return (parser_error("Camera already defined"));
	i = 1;
	trim_spaces(line, &i);
	set_camera_position(scene, line, &i);
	set_camera_direction(scene, line, &i);
	if (!check_axis_value(scene->camera.direction)
		|| equal(get_magnitude(scene->camera.direction), 0.0f))
		return (parser_error("Invalid camera orientation vector"));
	trim_spaces(line, &i);
	fov = ft_atof(line + i);
	if (fov < 0.0f || fov > 180.0f)
		return (parser_error("Camera FOV must be between 0 and 180"));
	scene->camera.fov = fov;
	scene->camera.direction = normalize(scene->camera.direction);
	if (scene->camera.direction.x == 0 && scene->camera.direction.y == 0
		&& scene->camera.direction.z == 0)
		scene->camera.direction.z = 1.0f;
	scene->has_camera = true;
	setup_camera(&scene->camera);
	return (1);
}

int	parse_ambient(t_scene *scene, char *line)
{
	int	i;

	i = 1;
	if (scene->has_ambient)
		return (parser_error("Ambient lighting already defined"));
	trim_spaces(line, &i);
	scene->ambient.ratio = parse_float(line, &i);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (parser_error("Ambient ratio must be between 0 and 1"));
	scene->ambient.color.r = (float)parse_int(line, &i) / 255.0f;
	scene->ambient.color.g = (float)parse_int(line, &i) / 255.0f;
	scene->ambient.color.b = (float)parse_int(line, &i) / 255.0f;
	if (!check_color(scene->ambient.color))
		return (parser_error("Ambient color must be between 0 and 255"));
	scene->has_ambient = true;
	return (1);
}
