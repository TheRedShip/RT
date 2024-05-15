/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloom.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:36:01 by marvin            #+#    #+#             */
/*   Updated: 2024/05/15 17:09:43 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calcul_treshold(t_vec3f ***result, t_vec3f **i, float treshold)
{
	int	pos[2];

	pos[1] = 0;
	while (pos[1] < HEIGHT)
	{
		pos[0] = 0;
		while (pos[0] < WIDTH)
		{
			if (i[pos[1]][pos[0]].x >= treshold || \
				i[pos[1]][pos[0]].y >= treshold || \
				i[pos[1]][pos[0]].z >= treshold)
				(*result)[pos[1]][pos[0]] = i[pos[1]][pos[0]];
			else
				(*result)[pos[1]][pos[0]] = (t_vec3f){0.0f, 0.0f, 0.0f};
			pos[0]++;
		}
		pos[1]++;
	}
}

t_vec3f	**bloom(t_scene *scene, t_vec3f **image)
{
	if (scene->mlx->is_bloom != 1)
		return (image);
	calcul_treshold(&scene->mlx->postpro_img, image, \
					scene->bloom->treshold);
	scene->mlx->postpro_img = sample(scene->mlx->postpro_img, \
				scene->bloom->mip_num, scene->bloom->blur_size);
	return (add_img(scene->mlx->postpro_img, image));
}
