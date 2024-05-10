/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_verify_parsing_settings.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:31:56 by marvin            #+#    #+#             */
/*   Updated: 2024/05/02 14:22:19 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_verify_ambient(t_scene *scene, char *line)
{
	char		**split;

	if (scene->ambient_light->has_seen)
		return (0);
	scene->ambient_light->has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 3)
		return (rt_return(split));
	if (rt_range_atof(split[1], 0.0, 3.0) == -1)
		return (rt_return (split));
	if (rt_atof3(split[2], 0, 255).x == -4242)
		return (rt_return (split));
	ft_free_tab((void **)(split));
	return (1);
}

int	rt_verify_camera(t_scene *scene, char *line)
{
	char		**split;

	if (scene->camera->has_seen)
		return (0);
	scene->camera->has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return (rt_return(split));
	if (rt_atof3(split[1], -1000.0, 1000.00).x == -4242)
		return (rt_return(split));
	if (rt_atof3(split[2], -2.0, 2.0).x == -4242)
		return (rt_return(split));
	if (rt_range_atoi(split[3], 0, 180) == -1)
		return (rt_return(split));
	if (rt_range_atoi(split[4], 0, 500) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int	rt_verify_light(t_scene *scene, char *line)
{
	char		**split;

	if (scene->lights->has_seen)
		return (0);
	scene->lights->has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return (rt_return(split));
	if (rt_atof3(split[1], -1000.0, 1000.00).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[2], 0.0, 1.0) == -1)
		return (rt_return(split));
	if (rt_atof3(split[3], 0, 255).x == -4242)
		return (rt_return(split));
	if (rt_range_atoi(split[4], 0, 1) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int	rt_verify_bloom(t_scene *scene, char *line)
{
	char		**split;

	if (scene->bloom->has_seen)
		return (0);
	scene->bloom->has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 4)
		return (rt_return(split));
	if (rt_range_atof(split[1], 0.0, 10.0) == -1)
		return (rt_return(split));
	if (rt_range_atoi(split[2], 0, 10) == -1)
		return (rt_return(split));
	if (rt_range_atoi(split[3], 0, 10) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int	rt_verify_kdtree(t_scene *scene, char *line)
{
	char		**split;

	if (scene->kdtree->has_seen)
		return (0);
	scene->kdtree->has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 2)
		return (rt_return(split));
	if (rt_range_atoi(split[1], 4, 5000) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}
