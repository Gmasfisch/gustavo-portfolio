/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:47:20 by gfischba          #+#    #+#             */
/*   Updated: 2026/07/03 15:57:05 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <stdlib.h>
# include "structs.h"
# include "helpers.h"
# include "../Libft/libft.h"

# define WIDTH  800
# define HEIGHT 600

# define EPSILON 0.00001

bool			equal(float a, float b);
t_tuple			vector(float x, float y, float z);
t_tuple			point(float x, float y, float z);
bool			is_point(t_tuple tuple);
bool			is_vector(t_tuple tuple);
t_tuple			add_tuples(t_tuple a, t_tuple b);
t_tuple			sub_tuple(t_tuple a, t_tuple b);
float			get_magnitude(t_tuple vector);
t_tuple			normalize(t_tuple tuple);
t_tuple			negate(t_tuple tuple);
t_tuple			scalar_multiplication(t_tuple vector, float scalar);
float			get_dot_product(t_tuple a, t_tuple b);
t_tuple			get_cross_product(t_tuple a, t_tuple b);
t_color			create_color(float r, float g, float b);
t_color			add_colors(t_color color1, t_color color2);
t_color			subtract_colors(t_color color1, t_color color2);
t_color			color_scalar_mult(t_color color, float scalar);
t_color			multiply_colors(t_color color1, t_color color2);
t_ray			create_ray(t_tuple origin, t_tuple direction);
t_tuple			position(t_ray *ray, float t);
t_ray			get_ray_for_pixel(t_camera camera, int px, int py);
t_tuple			reflect(t_tuple in, t_tuple normal);
int				is_shadowed(t_scene *scene, t_tuple point, t_tuple normal);
t_color			lighting(t_lighting lighting, int shadow);
int				sphere_intersections(t_object *obj, t_ray ray,
					t_intersection *arr, int start);
int				cylinder_intersections(t_object *obj, t_ray ray,
					t_intersection *arr, int start);
int				plane_intersections(t_object *obj, t_ray ray,
					t_intersection *arr, int start);
t_tuple			sphere_normal(t_sphere *sphere, t_tuple intersection_point);
t_tuple			cylinder_normal(t_object *obj, t_tuple intersection_point);
t_intersection	create_intersection(float t, void *object);
t_intersections	intersections(int n, t_intersection arr[]);
t_intersection	*hit(t_intersections *intersections);
void			my_mlx_pixel_put(t_mlx *data, int x, int y, t_color color);
void			render_scene(t_mlx *mlx, t_scene *scene);
void			render_pixel(t_mlx *mlx, t_scene *scene, int x, int y);
void			set_light(t_scene *scene, t_render_data *data);
int				get_file_data(char **argv, t_scene *scene);
int				parse_line(t_scene *scene, char *line);
int				parse_light(t_scene *scene, char *line);
int				parse_camera(t_scene *scene, char *line);
int				parse_ambient(t_scene *scene, char *line);
int				parse_shape(t_scene *scene, char *line);
int				parse_sphere(t_scene *scene, char *line);
int				parse_cylinder(t_scene *scene, char *line);
int				parse_plane(t_scene *scene, char *line);
void			set_default_material(t_scene *scene, t_color color,
					t_object_type type, void *shape);
void			set_camera_direction(t_scene *scene, char *line, int *i);
void			set_camera_position(t_scene *scene, char *line, int *i);
int				intersect_objects(t_scene *scene,
					t_ray ray, t_intersection *arr);
int				object_intersections(t_object *obj,
					t_ray ray, t_intersection *arr, int start);
void			get_t_values(float a, float b,
					float discriminant, float t[2]);
int				check_cap(t_object *obj, t_ray ray,
					t_intersection *arr, int start);
int				check_axis_value(t_tuple axis);
int				key_code(int keycode, t_app *app);
int				close_handler(t_app *app);
int				handle_expose(t_app *app);
int				check_color(t_color color);
t_matrix		compute_rotation_matrix(t_tuple ra, float an);
t_tuple			multiply_matrix_tuple(t_matrix m, t_tuple v);
t_matrix		identity_matrix(void);
t_matrix		transpose_matrix(t_matrix m);
void			init_cylinder_rotation(t_cylinder *cy);
void			cylinder_rotation(t_cylinder *cy,
					t_tuple *ray_direction, t_tuple *cy_ray);
int				init_pixel_data(t_scene *scene, int x, int y,
					t_render_data *px);
void			shade_pixel(t_scene *scene, t_render_data *px);
void			set_cylinder(char *line, int *i, t_cylinder *cy);
int				cap_hit(t_cylinder *cy, t_ray ray, float tcap);

#endif
