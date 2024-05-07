/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:38:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 21:38:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_lightsphere(char *line, t_scene *scene)
{
	t_objects	*objects;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	objects = rt_add_objects(scene, "sp");
	objects->origin = rt_atof3(s[1], -1000.0, 1000.0);
	objects->sphere->diameter = ft_atof(s[2]);
	objects->material.color = v_div_f(rt_atof3(s[3], 0.0f, 255.0f), 255.0f);
	objects->material.emission_power = ft_atof(s[4]);
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_lightquad(char *line, t_scene *scene)
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
	objects->material.color = v_div_f(rt_atof3(s[4], 0.0f, 255.0f), 255.0f);
	objects->material.emission_power = ft_atof(s[5]);
	objects->quad->normal = normalize(v_cross(objects->quad->up_corner, \
							objects->quad->right_corner));
	objects->quad->d = v_dot(objects->quad->normal, objects->origin);
	objects->quad->w = v_div_f(objects->quad->normal, \
					v_dot(objects->quad->normal, objects->quad->normal));
	ft_free_tab((void **)(s));
	return (1);
}