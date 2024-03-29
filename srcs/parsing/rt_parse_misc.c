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

#include "parsing.h"

int		rt_parse_ambient(char *line, t_scene **scene)
{
	char			**split;
	int				parameter;
	
	if ((*scene)->ambient_light)
		return (0);
	(*scene)->ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 3)
	{
		free((*scene)->ambient_light);
		return (0);
	}
	parameter = 0;
	while(*(split++))
	{
		if (parameter == 1)
			(*scene)->ambient_light->ratio = ft_atof(*split, 1);
		else if (parameter == 2)
			(*scene)->ambient_light->color = rt_atoi3(*split, 0, 255);
		if (parameter++ > 2)
			return (0);
	}
	return (1);
}

// int		rt_parse_camera(char *line, t_scene **scene)
// {
// 	char			**split;
// 	int				parameter;
	
// 	if ((*scene)->camera)
// 		return (0);
// 	(*scene)->camera = ft_calloc(1, sizeof(t_camera));
// 	split = ft_split(line, '\t');
// 	if (!split || ft_tab_len(split) != 3)
// 	{
// 		free((*scene)->camera);
// 		return (0);
// 	}
// 	parameter = 0;
// 	while(*(split++))
// 	{
// 		if (parameter == 1)
// 			(*scene)->camera->origin = rt_atof3(*split, -1000, 1000);
// 		else if (parameter == 2)
// 			(*scene)->camera->direction = rt_atof3(*split, -1, 1);
// 		else if (parameter == 3)
// 			(*scene)->camera->fov = rt_range(*split, 0, 180);
// 		if (parameter++ > 3)
// 			return (0);
// 	}
// 	return (1);
// }