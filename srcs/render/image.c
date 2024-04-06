/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:56:51 by marvin            #+#    #+#             */
/*   Updated: 2024/04/02 20:56:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f		**init_acc_img(t_scene *scene)
{
	t_vec3f	**acc_img;
	int		i;

	acc_img = ft_calloc(HEIGHT + 1, sizeof(t_vec3f *));
	if (!acc_img)
		rt_free_scene(scene);
	i = 0;
	while (i < HEIGHT)
	{
		acc_img[i] = ft_calloc(WIDTH + 1, sizeof(t_vec3f));
		if (!acc_img[i])
			rt_free_scene(scene);
		i++;
	}
	return (acc_img);
}

t_vec2f		get_uv(int x, int y)
{
	float		aspect_ratio;
	t_vec2f		uv;

	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	uv = (t_vec2f){(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
	uv.x = uv.x * 2.0f - 1.0f;
	uv.y = uv.y * 2.0f - 1.0f;
	uv.y = -uv.y;
	uv.x *= aspect_ratio;
	return (uv);
}