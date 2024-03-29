/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:18:46 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 20:18:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_parse_ambient(char *line, t_scene **scene)
{
	int		i;
	char	**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			(*scene)->ambient_light->ratio = ft_atof(split[i], 2);
		else if (i == 2)
			(*scene)->ambient_light->color = rt_atoi3(split[i], 0, 255);
	}
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_camera(char *line, t_scene **scene)
{
	int		i;
	char	**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);;
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			(*scene)->camera->origin = rt_atof3(split[i], -1000, 1000);
		else if (i == 2)
			(*scene)->camera->direction = rt_atof3(split[i], -1, 1);
		else if (i == 3)
			(*scene)->camera->fov = rt_range_atoi(split[i], 0, 180);
	}
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_light(char *line, t_scene **scene)
{
	int		i;
	char	**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);;
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			(*scene)->lights->origin = rt_atof3(split[i], -1000, 1000);
		else if (i == 2)
			(*scene)->lights->ratio = rt_range_atof(split[i], 0, 1);
		else if (i == 3)
			(*scene)->lights->color = rt_atoi3(split[i], 0, 255);
	}
	ft_free_tab((void **)(split));
	return (1);
}