/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_object2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 00:29:38 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 00:29:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_parse_lightquad(char *line, t_scene **scene)
{
	t_objects	*objects;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "qd");
	objects->origin = rt_atof3(split[1], -1000.0, 1000.0);
	objects->quad->right_corner = rt_atof3(split[2], -1000.0, 1000.0);
	objects->quad->up_corner = rt_atof3(split[3], -1000.0, 1000.0);
	objects->material.color = vec3f_div_f(rt_atof3(split[4], 0.0f, 255.0f), 255.0f);
	objects->material.emission_power = ft_atof(split[5]);
	objects->quad->normal = normalize(vec3f_cross(objects->quad->up_corner, objects->quad->right_corner));
	objects->quad->d = vec3f_dot(objects->quad->normal, objects->origin);
	objects->quad->w = vec3f_div_f(objects->quad->normal, vec3f_dot(objects->quad->normal,objects->quad->normal));
	ft_free_tab((void **)(split));
	return (1);
}