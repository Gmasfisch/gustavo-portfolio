/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:36:01 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:36:02 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	trim_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

float	parse_float(char *line, int *i)
{
	float	val;

	val = ft_atof(line + *i);
	while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '.'
			|| line[*i] == '-'))
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	trim_spaces(line, i);
	return (val);
}

int	parse_int(char *line, int *i)
{
	int	val;

	val = ft_atoi(line + *i);
	while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '-'))
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	trim_spaces(line, i);
	return (val);
}

int	check_axis_value(t_tuple axis)
{
	if (axis.x < -1.0f || axis.x > 1.0f
		|| axis.y < -1.0f || axis.y > 1.0f
		|| axis.z < -1.0f || axis.z > 1.0f)
	{
		write(2, "Error\nOrientation vector values must be in [-1, 1]\n", 51);
		return (0);
	}
	if (axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		write(2, "Error\nOrientation vector cannot be (0,0,0)\n", 43);
		return (0);
	}
	return (1);
}
