/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:38:41 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 16:38:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_sphere(char *line, t_scene *scene)
{
	t_objects	*o;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	o = rt_add_objects(scene, "sp");
	o->origin = rt_atof3(s[1], -1000.0, 1000.0);
	o->sphere->diameter = ft_atof(s[2]);
	o->material.color = v_div_f(rt_atof3(s[3], 0.0f, 4000.0f), 255.0f);
	if (rt_parse_material(scene, s[4], &(o->material)) == -1)
		return (rt_return(s));
	if (ft_tab_len(s) == 6)
	{
		o->sphere->rotation = rt_atof3(s[5], -180.0, 180.0);
		o->sphere->rotation.x = o->sphere->rotation.x * M_PI / 180.0;
		o->sphere->rotation.y = o->sphere->rotation.y * M_PI / 180.0;
		o->sphere->rotation.z = o->sphere->rotation.z * M_PI / 180.0;
	}
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_plane(char *line, t_scene *scene)
{
	char		**s;
	t_objects	*objects;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	objects = rt_add_objects(scene, "pl");
	objects->origin = rt_atof3(s[1], -1000.0, 1000.0);
	objects->plane->normal = rt_atof3(s[2], -1.0, 1.0);
	objects->material.color = v_div_f(rt_atof3(s[3], 0.0f, 4000.0f), 255.0f);
	if (rt_parse_material(scene, s[4], &(objects->material)) == -1)
		return (rt_return(s));
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_cylinder(char *line, t_scene *scene)
{
	t_objects	*objects;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	objects = rt_add_objects(scene, "cy");
	objects->origin = rt_atof3(s[1], -1000.0, 1000.0);
	objects->cylinder->orientation = rt_atof3(s[2], -1.0, 1.0);
	objects->cylinder->diameter = ft_atof(s[3]);
	objects->cylinder->height = ft_atof(s[4]);
	objects->material.color = v_div_f(rt_atof3(s[5], 0.0f, 4000.0f), 255.0f);
	if (objects->material.color.x > 1.0f || objects->material.color.y > 1.0f || \
		objects->material.color.z > 1.0f)
		objects->material.emission_power = (objects->material.color.x + \
											objects->material.color.y + \
											objects->material.color.z) / 3.0f;
	if (rt_parse_material(scene, s[6], &(objects->material)) == -1)
		return (rt_return(s));
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_quad(char *line, t_scene *scene)
{
	t_objects	*objects;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	objects = rt_add_objects(scene, "qd");
	objects->origin = rt_atof3(s[1], -1000.0, 1000.0);
	objects->quad->right_corner = rt_atof3(s[2], -1000.0, 1000.0);
	objects->quad->up_corner = rt_atof3(s[3], -1000.0, 1000.0);
	objects->material.color = v_div_f(rt_atof3(s[4], 0.0f, 4000.0f), 255.0f);
	if (rt_parse_material(scene, s[5], &(objects->material)) == -1)
		return (rt_return(s));
	objects->quad->normal = normalize(v_cross(objects->quad->up_corner, \
							objects->quad->right_corner));
	objects->quad->d = v_dot(objects->quad->normal, objects->origin);
	objects->quad->w = v_div_f(objects->quad->normal, \
					v_dot(objects->quad->normal, objects->quad->normal));
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_triangle(char *line, t_scene *scene)
{
	t_objects	*o;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	o = rt_add_objects(scene, "tr");
	o->origin = rt_atof3(s[1], -1000.0, 1000.0);
	o->triangle->pb = rt_atof3(s[2], -1000.0, 1000.0);
	o->triangle->pc = rt_atof3(s[3], -1000.0, 1000.0);
	o->triangle->edge[0] = v_sub_v(o->triangle->pb, o->origin);
	o->triangle->edge[1] = v_sub_v(o->triangle->pc, o->triangle->pb);
	o->triangle->edge[2] = v_sub_v(o->origin, o->triangle->pc);
	o->triangle->normal = \
		normalize(v_cross(o->triangle->edge[2], o->triangle->edge[0]));
	o->triangle->traverse = -v_dot(o->triangle->normal, o->origin);
	o->material.color = v_div_f(rt_atof3(s[4], 0.0f, 4000.0f), 255.0f);
	if (o->material.color.x > 1.0f || o->material.color.y > 1.0f || \
		o->material.color.z > 1.0f)
		o->material.emission_power = \
		(o->material.color.x + o->material.color.y + o->material.color.z) / 3;
	if (rt_parse_material(scene, s[5], &(o->material)) == -1)
		return (rt_return(s));
	ft_free_tab((void **)(s));
	return (1);
}
