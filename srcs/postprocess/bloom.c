/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloom.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:36:01 by marvin            #+#    #+#             */
/*   Updated: 2024/04/23 23:36:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void calcul_treshold(t_vec3f ***result, t_vec3f **image, float treshold)
{
	int	pos[2];

	pos[1] = 0;
	while (pos[1] < HEIGHT)
	{
		pos[0] = 0;
		while (pos[0] < WIDTH)
		{
			if (image[pos[1]][pos[0]].x > treshold || image[pos[1]][pos[0]].y > treshold || image[pos[1]][pos[0]].z > treshold)
				(*result)[pos[1]][pos[0]] = image[pos[1]][pos[0]]; 
			else
				(*result)[pos[1]][pos[0]] = (t_vec3f){0.0f, 0.0f, 0.0f};
			pos[0]++;
		}
		pos[1]++;
	}
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
			treshold[pos[1]][pos[0]] = vec3f_add_v(treshold[pos[1]][pos[0]], image[pos[1]][pos[0]]);
			pos[0]++;
		}
		pos[1]++;
	}
	return (treshold);
}

t_vec3f	**bloom(t_scene *scene, t_vec3f **image)
{
	calcul_treshold(&scene->mlx->postpro_img, image, 5.0f);
	// return (scene->mlx->postpro_img);
	return (add_img(scene->mlx->postpro_img, image));
	//return (image);
}