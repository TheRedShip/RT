/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_others.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:01:01 by marvin            #+#    #+#             */
/*   Updated: 2024/04/06 23:01:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			rt_parse_lightsphere(char *line, t_scene **scene)
{
	t_objects	*objects;
	char		**split;

	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "sp");
	objects->origin = rt_atof3(split[1], -1000.0, 1000.0);
	objects->sphere->diameter = ft_atof(split[2]);
	objects->material.color = vec3f_div_f(rt_atof3(split[3], 0.0f, 255.0f), 255.0f);
	objects->material.emission_power = ft_atof(split[4]);
	ft_free_tab((void **)(split));
	return (1);
}

int			rt_parse_glasssphere(char *line, t_scene **scene)
{
	t_objects	*objects;
	char		**split;

	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "sp");
	objects->material.type = MAT_DIELECTRIC;
	objects->origin = rt_atof3(split[1], -1000.0, 1000.0);
	objects->sphere->diameter = ft_atof(split[2]);
	objects->material.color = vec3f_div_f(rt_atof3(split[3], 0.0f, 255.0f), 255.0f);
	objects->material.refraction_index = ft_atof(split[4]);
	ft_free_tab((void **)(split));
	return (1);
}

void		setup_quad(t_objects *objects[6], char **split, int j)
{
	objects[j]->origin = rt_atof3(split[1], -1000.0, 1000.0);
	if (j == 0)
	{
		objects[j]->quad->up_corner = (t_vec3f){0, 0, -ft_atof(split[2])};
		objects[j]->quad->right_corner = (t_vec3f){ft_atof(split[2]), 0, 0};
	}
	else if (j == 1)
	{
		objects[j]->quad->up_corner = (t_vec3f){ft_atof(split[2]), 0, 0};
		objects[j]->quad->right_corner = (t_vec3f){0, ft_atof(split[3]), 0};
	}
	else if (j == 2)
	{
		objects[j]->quad->up_corner = (t_vec3f){0, ft_atof(split[3]), 0};
		objects[j]->quad->right_corner = (t_vec3f){0, 0, -ft_atof(split[2])};
	}
	else if (j == 3)
	{
		objects[j]->origin = vec3f_add_v(objects[j]->origin, (t_vec3f){ft_atof(split[2]), 0, 0});
		objects[j]->quad->up_corner = (t_vec3f){0, 0, -ft_atof(split[2])};
		objects[j]->quad->right_corner = (t_vec3f){0, ft_atof(split[3]), 0};
	}
	else if (j == 4)
	{
		objects[j]->origin = vec3f_add_v(objects[j]->origin, (t_vec3f){0, 0, -ft_atof(split[2])});
		objects[j]->quad->up_corner = (t_vec3f){0, ft_atof(split[3]), 0};
		objects[j]->quad->right_corner = (t_vec3f){ft_atof(split[2]), 0, 0};
	}
	else if (j == 5)
	{
		objects[j]->origin = vec3f_add_v(objects[j]->origin, (t_vec3f){0, ft_atof(split[3]), 0});
		objects[j]->quad->up_corner = (t_vec3f){ft_atof(split[2]), 0, 0};
		objects[j]->quad->right_corner = (t_vec3f){0, 0, -ft_atof(split[2])};
	}
}

int			rt_parse_cube(char *line, t_scene **scene)
{
	int			j;
	char		**split;
	t_objects	*objects[6];

	split = ft_split(line, '\t');
	if (!split)
		return (0);
	j = 0;
	while (j < 6)
	{
		objects[j] = rt_add_objects(scene, "qd");
		setup_quad(objects, split, j);
		objects[j]->quad->normal = normalize(vec3f_cross(objects[j]->quad->up_corner, objects[j]->quad->right_corner));
		objects[j]->quad->d = vec3f_dot(objects[j]->quad->normal, objects[j]->origin);
		objects[j]->quad->w = vec3f_div_f(objects[j]->quad->normal, vec3f_dot(objects[j]->quad->normal,objects[j]->quad->normal));
		objects[j]->material.color = vec3f_div_f(rt_atof3(split[5], 0.0f, 255.0f), 255.0f);
		if (rt_parse_material(*scene, split[6], &(objects[j]->material)) == -1)
				return (rt_return(split));
		j++;
	}
	ft_free_tab((void **)(split));
	return (1);
}

int			rt_parse_glasscube(char *line, t_scene **scene)
{
	int			j;
	char		**split;
	t_objects	*objects[6];

	split = ft_split(line, '\t');
	if (!split)
		return (0);
	j = 0;
	while (j < 6)
	{
		objects[j] = rt_add_objects(scene, "qd");
		objects[j]->material.type = MAT_DIELECTRIC;
		setup_quad(objects, split, j);
		objects[j]->quad->normal = normalize(vec3f_cross(objects[j]->quad->up_corner, objects[j]->quad->right_corner));
		objects[j]->quad->d = vec3f_dot(objects[j]->quad->normal, objects[j]->origin);
		objects[j]->quad->w = vec3f_div_f(objects[j]->quad->normal, vec3f_dot(objects[j]->quad->normal,objects[j]->quad->normal));
		objects[j]->material.color = vec3f_div_f(rt_atof3(split[5], 0.0f, 255.0f), 255.0f);
		objects[j]->material.refraction_index = ft_atof(split[6]);
		j++;
	}
	ft_free_tab((void **)(split));
	return (1);
}