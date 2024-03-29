/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:12:27 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 19:12:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>

# include "minirt.h"

typedef struct	s_ambient_light
{
	float		ratio;
	t_veci3		color;
}				t_ambient_light;

typedef struct	s_camera
{
	t_vecf3	origin;
	t_vecf3	direction;
	float		fov;
}				t_camera;

typedef struct	s_light
{
	t_vecf3	origin;
	float		ratio;
	t_veci3		color;
}				t_light;

typedef struct	s_sphere
{
	t_vecf3	origin;
	float		diameter;
	t_veci3		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vecf3	origin;
	t_vecf3	normal;
	t_veci3		color;
}				t_plane;

typedef struct	s_cylinder
{
	t_vecf3	origin;
	t_vecf3	orientation;
	float		diameter;
	float		height;
	t_veci3		color;
}				t_cylinder;

typedef struct	s_objects
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_objects;

typedef struct	s_scene
{
	t_ambient_light	*ambient_light;
	t_camera		*camera;
	t_light			*lights;
	t_objects		*objects;
}				t_scene;

int			rt_return(char **split);
int			rt_range_atoi(char *line, int min, int max);
float		rt_range_atof(char *line, float min, float max);
t_veci3		rt_atoi3(char *line, int min, int max);
t_vecf3		rt_atof3(char *line, float min, float max);

t_scene		*rt_parse(char *file);

int			rt_verify_camera(char *line);
int			rt_verify_ambient(char *line);
int			rt_verify_light(char *line);
int			rt_verify_sphere(char *line);
int			rt_verify_plane(char *line);
int			rt_verify_cylinder(char *line);


int			rt_parse_ambient(char *line, t_scene **scene);
int			rt_parse_camera(char *line, t_scene **scene);

#endif