/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:35:44 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:35:45 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	create_color(float r, float g, float b)
{
	t_color	new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	return (new_color);
}

t_color	add_colors(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r + color2.r;
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	return (new_color);
}

t_color	subtract_colors(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r - color2.r;
	new_color.g = color1.g - color2.g;
	new_color.b = color1.b - color2.b;
	return (new_color);
}

t_color	color_scalar_mult(t_color color, float scalar)
{
	t_color	new_color;

	new_color.r = color.r * scalar;
	new_color.g = color.g * scalar;
	new_color.b = color.b * scalar;
	return (new_color);
}

t_color	multiply_colors(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r * color2.r;
	new_color.g = color1.g * color2.g;
	new_color.b = color1.b * color2.b;
	return (new_color);
}
