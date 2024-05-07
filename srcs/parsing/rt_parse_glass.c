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

int	rt_parse_glasssphere(char *line, t_scene *scene)
{
	t_objects	*objects;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	objects = rt_add_objects(scene, "sp");
	objects->material.type = MAT_DIELECTRIC;
	objects->origin = rt_atof3(s[1], -1000.0, 1000.0);
	objects->sphere->diameter = ft_atof(s[2]);
	objects->material.color = v_div_f(rt_atof3(s[3], 0.0f, 255.0f), 255.0f);
	objects->material.refraction_index = ft_atof(s[4]);
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_glasscube(char *line, t_scene *scene)
{
	int			j;
	char		**s;
	t_objects	*o[6];

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	j = 0;
	while (j < 6)
	{
		o[j] = rt_add_objects(scene, "qd");
		o[j]->material.type = MAT_DIELECTRIC;
		setup_quad(o, s, j);
		o[j]->quad->normal = normalize(v_cross(o[j]->quad->up_corner, \
										o[j]->quad->right_corner));
		o[j]->quad->d = v_dot(o[j]->quad->normal, o[j]->origin);
		o[j]->quad->w = v_div_f(o[j]->quad->normal, \
						v_dot(o[j]->quad->normal, o[j]->quad->normal));
		o[j]->material.color = v_div_f(rt_atof3(s[5], 0, 255), 255);
		o[j]->material.refraction_index = ft_atof(s[6]);
		j++;
	}
	ft_free_tab((void **)(s));
	return (1);
}
