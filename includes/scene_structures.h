/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_structures.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:14:33 by marvin            #+#    #+#             */
/*   Updated: 2024/04/09 00:08:10 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_STRUCTURES_H
# define SCENE_STRUCTURES_H

# include "minirt.h"

typedef struct	s_objects	t_objects;
typedef struct	s_octree	t_octree;

typedef struct	s_camera
{
	float		fov;
	int			bounce;
	t_vec3f		origin;
	t_vec3f		direction;
	float		rotationMatrixX[3][3];
	float		rotationMatrixY[3][3];
}				t_camera;

typedef struct	s_ambient_light
{
	float		ratio;
	t_vec3f		color;
}				t_ambient_light;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	int		is_acc;
	int		is_bloom;
	int		is_octree;
	int		frame_index;
	int		antialiasing;
	t_data	img;
	t_vec3f	**acc_img;
	t_vec3f	**final_img;
	t_vec3f	**postpro_img;
}				t_mlx;

typedef struct	s_mouse
{
	t_vec2f pos;
	int		is_pressed;
}				t_mouse;

typedef struct	s_bloom
{
	float		treshold;
	int			blur_size;
	int			mip_num;
}				t_bloom;

typedef struct	s_light
{
	int			hard;
	float		ratio;
	t_vec3f		color;
	t_vec3f		origin;
}				t_light;

typedef struct	s_scene
{
	t_mouse			mouse;
	t_mlx			*mlx;
	t_bloom			*bloom;
	t_octree		*octree;
	t_objects		*objects;
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

typedef struct	s_sphere
{
	float		diameter;
}				t_sphere;

typedef struct	s_plane
{
	t_vec3f		normal;
}				t_plane;

typedef struct	s_quad
{
	float		d;
	float		witdh;
	float		height;
	t_vec3f		w;
	t_vec3f		normal;
	t_vec3f		up_corner;
	t_vec3f		right_corner;
}				t_quad;

typedef struct	s_cylinder
{
	float		height;
	float		diameter;
	t_vec3f		orientation;
}				t_cylinder;

typedef struct	s_ellipse
{
	float		a;
	float		b;
	float		c;
}				t_ellipse;

typedef struct	s_portal
{
	t_quad		quad;
	int			portal_id;
	int			linked_id;
	t_objects	*linked_portal;
}				t_portal;

typedef struct	s_texture
{
	int			exist;
	char		*path;
	t_data		data;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_material
{
	int			type;
	t_vec3f		color;
	t_texture	texture;
	int			checkered;
	float		roughness;
	float		specular_probs;
	float		emission_power;
	float		refraction_index;
}				t_material;

typedef struct	s_objects
{
	int					type;
	t_vec3f				origin;
	t_quad				*quad;
	t_plane				*plane;
	t_sphere			*sphere;
	t_portal			*portal;
	t_ellipse			*ellipse;
	t_cylinder			*cylinder;
	t_material			material;
	struct s_objects	*next;
}				t_objects;

#endif
