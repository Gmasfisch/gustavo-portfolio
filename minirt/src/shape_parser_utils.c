/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:45 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/07 14:32:14 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_color(char *line, int *i, t_color *color)
{
	color->r = (float)parse_int(line, i) / 255.0f;
	color->g = (float)parse_int(line, i) / 255.0f;
	color->b = (float)parse_int(line, i) / 255.0f;
	if (!check_color(*color))
	{
		perror("Error\na color is too high\n");
		return (0);
	}
	return (1);
}

void	set_plane(char *line, int *i, t_plane *pl)
{
	pl->point.x = parse_float(line, i);
	pl->point.y = parse_float(line, i);
	pl->point.z = parse_float(line, i);
	pl->point.w = 1.0f;
	pl->normal.x = parse_float(line, i);
	pl->normal.y = parse_float(line, i);
	pl->normal.z = parse_float(line, i);
	pl->normal.w = 0.0f;
}

void	set_cylinder(char *line, int *i, t_cylinder *cy)
{
	cy->radius = parse_float(line, i) / 2.0f;
	cy->height = parse_float(line, i);
}
