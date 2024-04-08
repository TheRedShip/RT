/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_verify_parsing_object2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 00:29:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 00:29:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_verify_lightquad(char *line)
{
	char		**split;

	split = ft_split(line, '\t');
	if (!split || ft_tab_len(split) != 6)
		return rt_return(split);
	if (rt_atof3(split[1], -1000.0, 1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[2], -1000.0, 1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[3], -1000.0, 1000.0).x == -4242)
		return rt_return(split);
	if (rt_atof3(split[4], 0, 255).x == -4242)
		return rt_return(split);
	if (rt_range_atof(split[5], 0.0, 1000.0) == -1)
		return (rt_return(split));
	ft_free_tab((void **)(split));
	return (1);
}
