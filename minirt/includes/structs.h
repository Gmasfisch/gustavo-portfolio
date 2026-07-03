/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 01:04:25 by mlemoula          #+#    #+#             */
/*   Updated: 2026/07/03 15:56:32 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minirt.h"

# define MAX_OBJECTS 10
# define MAX_INTERSECTIONS 20
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_tuple
{
	float		x;
	float		y;
	float		z;
	float		w;
}	t_tuple;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_camera
{
	t_tuple	position;
	t_tuple	direction;
	t_tuple	up;
	t_tuple	forward;
	t_tuple	right;
	float	fov;
}	t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_material
{
	t_color	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_object_type;

//radius = diameter / 2
typedef struct s_sphere
{
	t_tuple		center;
	float		radius;
}	t_sphere;

typedef struct s_matrix
{
	float	m[3][3];
}	t_matrix;

typedef struct s_cylinder
{
	t_tuple		center;
	t_tuple		axisv;
	float		radius;
	float		height;
	int			closed;
	t_matrix	rotation_matrix;
}	t_cylinder;

typedef struct s_plane
{
	t_tuple	point;
	t_tuple	normal;
}	t_plane;

typedef struct s_object
{
	t_object_type	type;
	t_material		material;
	void			*shape;
}	t_object;

typedef struct s_light
{
	t_tuple		position;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_intersection
{
	float		t;
	t_object	*object;
}	t_intersection;

typedef struct s_intersections
{
	int				count;
	t_intersection	data[MAX_INTERSECTIONS];
}	t_intersections;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	object[MAX_OBJECTS];
	int			object_count;
	bool		has_ambient;
	bool		has_camera;
	bool		has_light;
}	t_scene;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_app
{
	t_mlx	*mlx;
	t_scene	*scene;
}	t_app;

typedef struct s_intersection_data
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_ray	local_ray;
	float	t[2];
}	t_intersection_data;

typedef struct s_camera_data
{
	float	aspect;
	float	half_view;
	float	world_x;
	float	world_y;
}	t_camera_data;

#endif
