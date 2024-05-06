/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:30:00 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 00:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	**add_img(t_vec3f **treshold, t_vec3f **image)
{
	int	pos[2];

	pos[1] = 0;
	while (pos[1] < HEIGHT)
	{
		pos[0] = 0;
		while (pos[0] < WIDTH)
		{
			treshold[pos[1]][pos[0]] = \
				vec3f_add_v(treshold[pos[1]][pos[0]], image[pos[1]][pos[0]]);
			pos[0]++;
		}
		pos[1]++;
	}
	return (treshold);
}

void	dup_img(t_vec3f **image, t_vec3f **image2, t_vec2f resolution)
{
	int		pos[2];

	pos[1] = 0;
	while (pos[1] < resolution.y)
	{
		pos[0] = 0;
		while (pos[0] < resolution.x)
		{
			image[pos[1]][pos[0]] = image2[pos[1]][pos[0]];
			pos[0]++;
		}
		pos[1]++;
	}
}
