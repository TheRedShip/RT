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

int		rt_parse_material(t_scene *scene, char *str, t_material *material)
{
	char		**split;

	split = ft_split(str, ',');
	if (!split)
		return (-1);
	material->roughness = ft_atof(split[0]);
	material->specular_probs = ft_atof(split[1]);
	if (ft_tab_len(split) == 3 && ft_atoi(split[2]) == 1)
		material->checkered = 1;
	if (ft_tab_len(split) == 4)
		material->texture = init_texture(scene, split[3]);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_sphere(char *line, t_scene **scene)
{
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "sp");
	objects->origin = rt_atof3(split[1], -1000.0, 10000.0);
	objects->sphere->diameter = ft_atof(split[2]);
	objects->material.color = vec3f_div_f(rt_atof3(split[3], 0.0f, 255.0f), 255.0f);
	if (rt_parse_material(*scene, split[4], &(objects->material)) == -1)
			return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_plane(char *line, t_scene **scene)
{
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "pl");
	objects->origin = rt_atof3(split[1], -1000.0, 10000.0);
	objects->plane->normal = rt_atof3(split[2], -1.0, 1.0);
	objects->material.color = vec3f_div_f(rt_atof3(split[3], 0.0f, 255.0f), 255.0f);
	if (rt_parse_material(*scene, split[4], &(objects->material)) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_cylinder(char *line, t_scene **scene)
{
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "cy");
	objects->origin = rt_atof3(split[1], -1000.0, 10000.0);
	objects->cylinder->orientation = rt_atof3(split[2], -1.0, 1.0);
	objects->cylinder->diameter = ft_atof(split[3]);
	objects->cylinder->height = ft_atof(split[4]);
	objects->material.color = vec3f_div_f(rt_atof3(split[5], 0.0f, 255.0f), 255.0f);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_quad(char *line, t_scene **scene)
{
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "qd");
	objects->origin = rt_atof3(split[1], -1000.0, 10000.0);
	objects->quad->right_corner = rt_atof3(split[2], -1000.0, 10000.0);
	objects->quad->up_corner = rt_atof3(split[3], -1000.0, 10000.0);
	objects->material.color = vec3f_div_f(rt_atof3(split[4], 0.0f, 255.0f), 255.0f);
	if (rt_parse_material(*scene, split[5], &(objects->material)) == -1)
		return (rt_return(split));
	objects->quad->normal = normalize(vec3f_cross(objects->quad->up_corner, objects->quad->right_corner));
	objects->quad->d = vec3f_dot(objects->quad->normal, objects->origin);
	objects->quad->w = vec3f_div_f(objects->quad->normal, vec3f_dot(objects->quad->normal,objects->quad->normal));
	ft_free_tab((void **)(split));
	return (1);
}