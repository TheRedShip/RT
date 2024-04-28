/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_verify_parsing_objects.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:05:56 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 16:05:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_verify_material(char *str)
{
	char		**split;

	split = ft_split(str, ',');
	if (!split || (ft_tab_len(split) != 3 && ft_tab_len(split) != 2 && ft_tab_len(split) != 4))
		return (rt_return(split));
	if (rt_range_atof(split[0], 0.0, 1.0) == -1)
		return (rt_return(split));
	if (rt_range_atof(split[1], 0.0, 1.0) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);

}

int		rt_verify_sphere(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return rt_return(split);
	if (rt_atof3(split[1], -1000.0,1000.0).x == -4242)
		return rt_return(split);
	if (rt_range_atof(split[2], 0.0, 10000.0) == -1)
		return rt_return(split);
	if (rt_atof3(split[3], 0, 255).x == -4242)
		return rt_return(split);
	if (rt_verify_material(split[4]) == 0)
		return rt_return(split);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_plane(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return rt_return(split);
	if (rt_atof3(split[1], -1000.0,1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[2], -1.0, 1.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[3], 0, 255).x == -4242)
		return rt_return(split);
	if (rt_verify_material(split[4]) == 0)
		return rt_return(split);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_cylinder(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 7)
		return rt_return(split);
	if (rt_atof3(split[1], -1000.0,1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[2], -1.0, 1.0).x == -4242)
		return rt_return(split);
	if (rt_range_atof(split[3], 0.0, 10000.0) == -1)
		return rt_return(split);
	if (rt_range_atof(split[4], 0.0, 10000.0) == -1)
		return rt_return(split);
	if (rt_atof3(split[5], 0, 255).x == -4242)
		return rt_return(split);
	if (rt_verify_material(split[6]) == 0)
		return rt_return(split);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_quad(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 6)
		return rt_return(split);
	if (rt_atof3(split[1], -1000.0,1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[2], -1000.0,1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[3], -1000.0,1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[4], 0, 255).x == -4242)
		return rt_return(split);
	if (rt_verify_material(split[5]) == 0)
		return rt_return(split);
	ft_free_tab((void **)(split));
	return (1);
}