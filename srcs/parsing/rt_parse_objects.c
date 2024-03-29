/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:38:41 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 16:38:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_parse_sphere(char *line, t_scene **scene)
{
	int			i;
	t_sphere	*sphere;
	char		**split;
	
	split = ft_split(line, '\t');
	if (!split)
		return (0);
	sphere = rt_add_objects(scene, "sp")->sphere;
	i = -1;
	while (split[++i])
	{
		if (i == 1)
			sphere->origin = rt_atof3(split[i], -1000.0, 1000.0);
		else if (i == 2)
			sphere->diameter = rt_range_atof(split[i], 0.0, 1000.0);
		else if (i == 3)
			sphere->color = rt_atoi3(split[i], 0, 255);
	}
	ft_free_tab((void **)(split));
	return (1);
}