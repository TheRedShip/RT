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

int		rt_parse_material(char *str, t_material *material)
{
	char		**split;

	split = ft_split(str, ',');
	if (!split)
		return (-1);
	material->roughness = ft_atof(split[0]);
	material->specular_probs = ft_atof(split[1]);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_sphere(char *line, t_scene **scene)
{
	int			i;
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "sp");
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			objects->origin = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 2)
			objects->sphere->diameter = ft_atof(split[i]);
		else if (i == 3)
			objects->material.color = vec3f_div_f(rt_atof3(split[i], 0.0f, 255.0f), 255.0f);
		else if (i == 4 && rt_parse_material(split[i], &(objects->material)) == -1)
			return (rt_return(split));
	}
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_plane(char *line, t_scene **scene)
{
	int			i;
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "pl");
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			objects->origin = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 2)
			objects->plane->normal = rt_atof3(split[i], -1.0, 1.0);
		else if (i == 3)
			objects->material.color = vec3f_div_f(rt_atof3(split[i], 0.0f, 255.0f), 255.0f);
		else if (i == 4 && rt_parse_material(split[i], &(objects->material)) == -1)
			return (rt_return(split));
	}
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_cylinder(char *line, t_scene **scene)
{
	int			i;
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "cy");
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			objects->origin = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 2)
			objects->cylinder->orientation = rt_atof3(split[i], -1.0, 1.0);
		else if (i == 3)
			objects->cylinder->diameter = ft_atof(split[i]);
		else if (i == 4)
			objects->cylinder->height = ft_atof(split[i]);
		else if (i == 5)
			objects->material.color = vec3f_div_f(rt_atof3(split[i], 0.0f, 255.0f), 255.0f);
	}
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_quad(char *line, t_scene **scene)
{
	int			i;
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "qd");
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			objects->origin = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 2)
			objects->quad->right_corner = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 3)
			objects->quad->up_corner = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 4)
			objects->quad->size = ft_atof(split[i]);
		else if (i == 5)
			objects->material.color = vec3f_div_f(rt_atof3(split[i], 0.0f, 255.0f), 255.0f);
		else if (i == 6 && rt_parse_material(split[i], &(objects->material)) == -1)
			return (rt_return(split));
	}
	objects->quad->normal = normalize(vec3f_cross(objects->quad->up_corner, objects->quad->right_corner));
	objects->quad->d = vec3f_dot(objects->quad->normal, objects->origin);
	objects->quad->w = vec3f_div_f(objects->quad->normal, vec3f_dot(objects->quad->normal,objects->quad->normal));
	ft_free_tab((void **)(split));
	return (1);
}