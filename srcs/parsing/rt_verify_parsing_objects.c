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
	if (!split || ft_tab_len(split) != 3)
		return (rt_return(split));
	if (rt_range_atof(split[0], 0.0, 1000.0) == -1)
		return (rt_return(split));
	if (rt_range_atof(split[1], 0.0, 1.0) == -1)
		return (rt_return(split));
	if (rt_range_atof(split[2], 0.0, 1.0) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);

}

int		rt_verify_sphere(char *line)
{
	int			i;
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return rt_return(split);
	i = -1;
	while (split[++i])
	{
		if (i == 1 && rt_atof3(split[i], -1000.0, 1000.0).x == -4242)
			return rt_return(split);
		if (i == 2 && rt_range_atof(split[i], 0.0, 1000.0) == -1)
			return rt_return(split);
		if (i == 3 && rt_atof3(split[i], 0, 255).x == -4242)
			return rt_return(split);
		if (i == 4 && rt_verify_material(split[i]) == -0)
			return rt_return(split);
	}
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_plane(char *line)
{
	int			i;
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return rt_return(split);
	i = -1;
	while (split[++i])
	{
		if (i == 1 && rt_atof3(split[i], -1000.0, 1000.0).x == -4242)
			return rt_return(split);
		if (i == 2 && rt_atof3(split[i], -1.0, 1.0).x == -4242)
			return rt_return(split);
		if (i == 3 && rt_atof3(split[i], 0, 255).x == -4242)
			return rt_return(split);
		if (i == 4 && rt_verify_material(split[i]) == -1)
			return rt_return(split);
	}
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_cylinder(char *line)
{
	int			i;
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 6)
		return rt_return(split);
	i = -1;
	while (split[++i])
	{
		if (i == 1 && rt_atof3(split[i], -1000.0, 1000.0).x == -4242)
			return rt_return(split);
		if (i == 2 && rt_atof3(split[i], -1.0, 1.0).x == -4242)
			return rt_return(split);
		if (i == 3 && rt_range_atof(split[i], 0.0, 1000.0) == -1)
			return rt_return(split);
		if (i == 4 && rt_range_atof(split[i], 0.0, 1000.0) == -1)
			return rt_return(split);
		if (i == 5 && rt_atof3(split[i], 0, 255).x == -4242)
			return rt_return(split);
	}
	ft_free_tab((void **)(split));
	return (1);
}