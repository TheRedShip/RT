/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_verify_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:31:56 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 15:31:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_verify_ambient(char *line)
{
	char		**split;
	static int	has_seen = 0;

	if (has_seen)
		return (0);
	has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 3)
		return rt_return(split);
	if (rt_range_atof(split[1], 0.0, 3.0) == -1)
		return (rt_return(split));
	if (rt_atof3(split[2], 0, 255).x == -4242)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_camera(char *line)
{
	char		**split;
	static int	has_seen = 0;

	if (has_seen)
		return (0);
	has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return rt_return(split);
	if (rt_atof3(split[1], -1000.0,1000.00).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[2], -1.0, 1.0).x == -4242)
		return rt_return(split);
	if (rt_range_atoi(split[3], 0, 180) == -1)
		return rt_return(split);
	if (rt_range_atoi(split[4], 0, 500) == -1)
		return rt_return(split);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_light(char *line)
{
	char		**split;
	static int	has_seen = 0;

	if (has_seen)
		return (0);
	has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 5)
		return rt_return(split);
	if (rt_atof3(split[1], -1000.0,1000.00).x == -4242)
		return rt_return(split);
	if (rt_range_atof(split[2], 0.0, 1.0) == -1)
		return rt_return(split);
	if (rt_atof3(split[3], 0, 255).x == -4242)
		return rt_return(split);
	if (rt_range_atoi(split[4], 0, 1) == -1)
		return rt_return(split);
	ft_free_tab((void **)(split));
	return (1);
}

int		rt_verify_bloom(char *line)
{
	char		**split;
	static int	has_seen = 0;

	if (has_seen)
		return (0);
	has_seen = 1;
	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 4)
		return rt_return(split);
	if (rt_range_atof(split[1], 0.0, 10.0) == -1)
		return rt_return(split);
	if (rt_range_atoi(split[2], 0, 10) == -1)
		return rt_return(split);
	if (rt_range_atoi(split[3], 0, 13) == -1)
		return rt_return(split);
	ft_free_tab((void **)(split));
	return (1);
}
