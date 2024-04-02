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
	t_vec3f		origin;
	t_vec3f		direction;
	float		fov;
}				t_camera;

typedef struct	s_light
{
	t_vec3f		origin;
	float		ratio;
	t_vec3f		color;
}				t_light;

typedef struct	s_sphere
{
	float		diameter;
}				t_sphere;

typedef struct	s_plane
{
	t_vec3f		normal;
}				t_plane;

typedef struct	s_cylinder
{
	t_vec3f		orientation;
	float		diameter;
	float		height;
}				t_cylinder;

typedef struct	s_objects
{
	t_vec3f				origin;
	t_vec3f				color;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
	int					type;
	struct s_objects	*next;
}				t_objects;

// typedef struct	s_mlx
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	*img;
// }				t_mlx;



#endif