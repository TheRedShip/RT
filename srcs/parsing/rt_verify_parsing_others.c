/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_verify_parsing_others.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:56:10 by marvin            #+#    #+#             */
/*   Updated: 2024/04/06 22:56:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_verify_lightsphere(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return (rt_return(split));
	if (rt_atof3(split[1], -10000.0, 10000.0).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[2], 0.0, 10000.0) == -1)
		return (rt_return(split));
	if (rt_atof3(split[3], 0, 255).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[4], 0.0, 10000.0) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int	rt_verify_glasssphere(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return (rt_return(split));
	if (rt_atof3(split[1], -10000.0, 10000.0).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[2], 0.0, 10000.0) == -1)
		return (rt_return(split));
	if (rt_atof3(split[3], 0, 255).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[4], 0.0, 100.0) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int	rt_verify_cube(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 7)
		return (rt_return(split));
	if (rt_atof3(split[1], -10000.0, 10000.0).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[2], 0.0, 10000.0) == -1)
		return (rt_return(split));
	if (rt_range_atof(split[3], 0.0, 10000.0) == -1)
		return (rt_return(split));
	if (rt_atof3(split[4], 0, 1).x == -4242)
		return (rt_return(split));
	if (rt_atof3(split[5], 0, 255).x == -4242)
		return (rt_return(split));
	if (rt_verify_material(split[6]) == 0)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int	rt_verify_glasscube(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 7)
		return (rt_return(split));
	if (rt_atof3(split[1], -10000.0, 10000.0).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[2], 0.0, 10000.0) == -1)
		return (rt_return(split));
	if (rt_range_atof(split[3], 0.0, 10000.0) == -1)
		return (rt_return(split));
	if (rt_atof3(split[4], 0, 1).x == -4242)
		return (rt_return(split));
	if (rt_atof3(split[5], 0, 255).x == -4242)
		return (rt_return(split));
	if (rt_range_atof(split[6], 0, 100) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}