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

t_vec3f	**init_img(t_scene *scene, int width, int height)
{
	t_vec3f	**acc_img;
	int		i;

	acc_img = ft_calloc(height + 1, sizeof(t_vec3f *));
	if (!acc_img)
		rt_free_scene(scene, 1);
	i = 0;
	while (i < height)
	{
		acc_img[i] = ft_calloc(width + 1, sizeof(t_vec3f));
		if (!acc_img[i])
			rt_free_scene(scene, 1);
		i++;
	}
	return (acc_img);
}

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
				v_add_v(treshold[pos[1]][pos[0]], image[pos[1]][pos[0]]);
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
