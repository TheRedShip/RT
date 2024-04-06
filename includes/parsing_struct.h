/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:53:06 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 16:53:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STRUCT_H
# define PARSING_STRUCT_H

# include "minirt.h"

typedef struct	s_ambient_light
{
	float		ratio;
	t_vec3f		color;
}				t_ambient_light;

typedef struct	s_camera
{
	float		fov;
	t_vec3f		origin;
	t_vec3f		direction;
	float		rotationMatrixX[3][3];
	float		rotationMatrixY[3][3];
}				t_camera;

typedef struct	s_light
{
	float		ratio;
	t_vec3f		color;
	t_vec3f		origin;
}				t_light;

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
	float		size;
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

typedef struct	s_material
{
	int			type;
	t_vec3f		color;
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
	t_cylinder			*cylinder;
	t_material			material;
	struct s_objects	*next;
}				t_objects;


#endif