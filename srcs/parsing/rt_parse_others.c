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
		else if (i == 4)
			objects->material.emission_power = ft_atof(split[i]);
	}
	ft_free_tab((void **)(split));
	return (1);
}

int			rt_parse_glasssphere(char *line, t_scene **scene)
{
	int			i;
	t_objects	*objects;
	char		**split;

	split = ft_split(line, '\t');
	if (!split)
		return (0);
	objects = rt_add_objects(scene, "sp");
	objects->material.type = MAT_DIELECTRIC;
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			objects->origin = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 2)
			objects->sphere->diameter = ft_atof(split[i]);
		else if (i == 3)
			objects->material.color = vec3f_div_f(rt_atof3(split[i], 0.0f, 255.0f), 255.0f);
		else if (i == 4)
			objects->material.refraction_index = ft_atof(split[i]);
	}
	ft_free_tab((void **)(split));
	return (1);
}