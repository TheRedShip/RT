/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_structures.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:14:33 by marvin            #+#    #+#             */
/*   Updated: 2024/05/12 18:01:50 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_STRUCTURES_H
# define SCENE_STRUCTURES_H

# include "minirt.h"

typedef struct s_bvh		t_bvh;
typedef struct s_kd_tree	t_kd_tree;
typedef struct s_objects	t_objects;

typedef struct s_camera
{
	int			has_seen;
	float		fov;
	int			bounce;
	t_vec3f		origin;
	t_vec3f		direction;
	float		rotation_matrix_x[3][3];
	float		rotation_matrix_y[3][3];
}				t_camera;

typedef struct s_ambient_light
{
	int			has_seen;
	float		ratio;
	t_vec3f		color;
}				t_ambient_light;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size;
	int		endian;
}				t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		is_acc;
	int		is_bloom;
	int		frame_index;
	int		antialiasing;
	t_data	img;
	t_vec3f	**acc_img;
	t_vec3f	**final_img;
	t_vec3f	**postpro_img;
}				t_mlx;

typedef struct s_mouse
{
	t_vec2f	pos;
	int		is_pressed;
}				t_mouse;

typedef struct s_bloom
{
	int			has_seen;
	float		treshold;
	int			blur_size;
	int			mip_num;
}				t_bloom;

typedef struct s_light
{
	int			has_seen;
	float		ratio;
	t_vec3f		color;
	t_vec3f		origin;
}				t_light;

typedef struct s_server
{
	int				fd;
	char			*ip;
	int				stop;
	uint16_t		port;
	uint64_t		acc_start_time;
	uint64_t		acc_block_received;
	uint64_t		send_time;
	uint8_t			nb_acc;
	pthread_mutex_t	mutex;
}	t_server;

typedef struct s_scene
{
	char			*name;
	t_mouse			mouse;
	t_server		server;
	t_bvh			*bvh;
	t_mlx			*mlx;
	t_bloom			*bloom;
	t_kd_tree		*kdtree;
	t_objects		*objects;
	t_objects		*last_objects;
	t_light			*lights;
	t_camera		*camera;
	t_ambient_light	*ambient_light;
}				t_scene;

typedef struct s_threads
{
	int			id;
	pthread_t	thread;
	t_scene		*scene;
}				t_threads;

typedef struct s_sphere
{
	t_vec3f		rotation;
	float		diameter;
}				t_sphere;

typedef struct s_plane
{
	t_vec3f		normal;
}				t_plane;

typedef struct s_quad
{
	float		d;
	float		witdh;
	float		height;
	t_vec3f		w;
	t_vec3f		normal;
	t_vec3f		up_corner;
	t_vec3f		right_corner;
}				t_quad;

typedef struct s_cylinder
{
	float		height;
	float		diameter;
	t_vec3f		orientation;
}				t_cylinder;

typedef struct s_ellipse
{
	float		a;
	float		b;
	float		c;
}				t_ellipse;

typedef struct s_portal
{
	t_quad		quad;
	int			portal_id;
	int			linked_id;
	t_objects	*linked_portal;
}				t_portal;

typedef struct s_triangle
{
	t_vec3f		pb;
	t_vec3f		pc;
	t_vec3f		normal;
	t_vec3f		edge[3];
	float		traverse;
}				t_triangle;

#endif
