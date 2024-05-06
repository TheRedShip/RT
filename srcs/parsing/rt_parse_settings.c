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

int		rt_parse_ambient(char *line, t_scene *scene)
{
	char	**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	scene->ambient_light->ratio = ft_atof(split[1]);
	scene->ambient_light->color = vec3f_div_f(rt_atof3(split[2], 0.0f, 255.0f), 255.0f);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_camera(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, '\t');
	if (!split)
		return (0);;
	scene->camera->origin = rt_atof3(split[1], -1000, 1000);

	scene->camera->direction = rt_atof3(split[2], -1, 1);
	scene->camera->direction.z = scene->camera->direction.x;
	scene->camera->direction.x = scene->camera->direction.y;
	scene->camera->direction.y = scene->camera->direction.z;
	scene->camera->direction.z = -1;
	
	scene->camera->fov = ft_atoi(split[3]);
	scene->camera->bounce = ft_atoi(split[4]);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_light(char *line, t_scene *scene)
{
	char	**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	scene->lights->origin = rt_atof3(split[1], -1000, 1000);
	scene->lights->ratio = ft_atof(split[2]);
	scene->lights->color = vec3f_div_f(rt_atof3(split[3], 0.0f, 255.0f), 255.0f);
	scene->lights->hard = ft_atoi(split[4]);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_parse_bloom(char *line, t_scene *scene)
{
	char	**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	scene->bloom->treshold = ft_atof(split[1]);
	scene->bloom->blur_size = ft_atoi(split[2]);
	scene->bloom->mip_num = ft_atoi(split[3]);
	ft_free_tab((void **)(split));
	return (1);
}