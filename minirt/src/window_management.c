/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:36:59 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:37:00 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clean_exit(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->scene->object_count)
	{
		if (app->scene->object[i].shape)
			free(app->scene->object[i].shape);
		i++;
	}
	if (app->mlx->img)
		mlx_destroy_image(app->mlx->mlx, app->mlx->img);
	if (app->mlx->win)
		mlx_destroy_window(app->mlx->mlx, app->mlx->win);
	if (app->mlx->mlx)
		free(app->mlx->mlx);
	exit(0);
}

int	handle_expose(t_app *app)
{
	if (app->mlx->win && app->mlx->img)
		mlx_put_image_to_window(app->mlx->mlx,
			app->mlx->win, app->mlx->img, 0, 0);
	return (0);
}

int	key_code(int keycode, t_app *app)
{
	if (keycode == 65307)
		clean_exit(app);
	return (0);
}

int	close_handler(t_app *app)
{
	clean_exit(app);
	return (0);
}
