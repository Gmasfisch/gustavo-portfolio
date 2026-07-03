/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:36:46 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 14:46:30 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

void	my_mlx_pixel_put(t_mlx *data, int x, int y, t_color color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	r = clamp((int)(color.r * 255.0f), 0, 255);
	g = clamp((int)(color.g * 255.0f), 0, 255);
	b = clamp((int)(color.b * 255.0f), 0, 255);
	i = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	data->addr[i] = (unsigned char)b;
	data->addr[i + 1] = (unsigned char)g;
	data->addr[i + 2] = (unsigned char)r;
}

void	render_scene(t_mlx *mlx, t_scene *scene)
{
	int	x;
	int	y;

	(void) scene;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(mlx, scene, x, y);
			x++;
		}
		y++;
	}
}

void	render_pixel(t_mlx *mlx, t_scene *scene, int x, int y)
{
	t_render_data	data;
	t_color			color;

	ft_bzero(&data, sizeof(t_render_data));
	if (!init_pixel_data(scene, x, y, &data))
	{
		my_mlx_pixel_put(mlx, x, y, color_black());
		return ;
	}
	shade_pixel(scene, &data);
	color = lighting(data.lgt, data.shadow);
	my_mlx_pixel_put(mlx, x, y, color);
}
