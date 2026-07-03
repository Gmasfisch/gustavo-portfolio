/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:02:48 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/07 13:36:17 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_scene	scene;
	t_app	app;

	if (argc != 2)
		return (write(2, "Error\nWrong arguments\n", 22), 1);
	ft_bzero(&scene, sizeof(t_scene));
	ft_bzero(&mlx, sizeof(t_mlx));
	app.mlx = &mlx;
	app.scene = &scene;
	if (!get_file_data(argv, &scene))
		return (-1);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "miniRT");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img,
			&mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	render_scene(&mlx, &scene);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_hook(mlx.win, 17, 0, close_handler, &app);
	mlx_key_hook(mlx.win, key_code, &app);
	mlx_expose_hook(mlx.win, handle_expose, &app);
	mlx_loop(mlx.mlx);
	return (0);
}
