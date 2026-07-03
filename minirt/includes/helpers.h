/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 01:06:05 by mlemoula          #+#    #+#             */
/*   Updated: 2026/02/06 01:06:06 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include "structs.h"

typedef struct s_light_color
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
}	t_light_color;

typedef struct s_lighting
{
	t_material	material;
	t_light		light;
	t_ambient	ambient;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
}	t_lighting;

typedef struct s_render_data
{
	t_ray			ray;
	t_intersection	arr[MAX_INTERSECTIONS];
	t_intersections	xs;
	t_intersection	*closest;
	t_tuple			world_point;
	t_tuple			normal;
	t_lighting		lgt;
	int				count;
	int				shadow;
}	t_render_data;

t_color	color_black(void);
t_color	compute_ambient(t_material m, t_ambient a);
t_color	compute_diffuse(t_material m, t_light l, float dot);
t_color	compute_specular(t_material m, t_light l,
			t_tuple reflectv, t_tuple eyev);
t_tuple	normal_at(t_object *obj, t_tuple point);
float	ft_atof(const char *str);
void	trim_spaces(char *line, int *i);
float	parse_float(char *line, int *i);
int		parse_int(char *line, int *i);
int		parser_error(const char *msg);
void	cleanup_scene_objects(t_scene *scene);
int		check_object_limit(t_scene *scene);
void	setup_camera(t_camera *camera);
void	solve_quadratic(t_intersection_data *ldata, t_cylinder *cy);
t_ray	transform_ray_to_local(t_cylinder *cy, t_ray ray);
int		set_color(char *line, int *i, t_color *color);
void	set_plane(char *line, int *i, t_plane *pl);

#endif