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
	t_veci3		color;
}				t_ambient_light;

typedef struct	s_camera
{
	t_vecf3		origin;
	t_vecf3		direction;
	float		fov;
}				t_camera;

typedef struct	s_light
{
	t_vecf3		origin;
	float		ratio;
	t_veci3		color;
}				t_light;

typedef struct	s_sphere
{
	t_vecf3		origin;
	float		diameter;
	t_veci3		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vecf3		origin;
	t_vecf3		normal;
	t_veci3		color;
}				t_plane;

typedef struct	s_cylinder
{
	t_vecf3		origin;
	t_vecf3		orientation;
	float		diameter;
	float		height;
	t_veci3		color;
}				t_cylinder;

typedef struct	s_objects
{
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
	int					type;
	struct s_objects	*next;
}				t_objects;

typedef struct	s_scene
{
	t_ambient_light	*ambient_light;
	t_camera		*camera;
	t_light			*lights;
	t_objects		*objects;
}				t_scene;

#endif