/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:27:42 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 00:27:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	**down_sample_2x(t_vec3f **image, t_vec2f resolution)
{
	int		pos[2];

	pos[1] = 0;
	while (pos[1] < resolution.y)
	{
		pos[0] = 0;
		while (pos[0] < resolution.x)
		{
			image[pos[1]][pos[0]] = image[pos[1] * 2][pos[0] * 2];
			pos[0]++;
		}
		pos[1]++;
	}
	return (image);
}

t_vec3f	**up_sample_2x(t_vec3f **image, t_vec2f resolution)
{
	int		pos[2];
	t_vec3f	**tmp;

	tmp = init_img(NULL, resolution.x * 2, resolution.y * 2);
	pos[1] = 0;
	while (pos[1] < resolution.y * 2)
	{
		pos[0] = 0;
		while (pos[0] < resolution.x * 2)
		{
			tmp[pos[1]][pos[0]] = image[pos[1] / 2][pos[0] / 2];
			pos[0]++;
		}
		pos[1]++;
	}
	dup_img(image, tmp, (t_vec2f){resolution.x * 2, resolution.y * 2});
	ft_free_tab((void **)tmp);
	return (image);
}

t_vec3f	**sample(t_vec3f **image, int mip_num, int blur_size)
{
	t_vec2f	resolution;
	int		i;

	resolution = (t_vec2f){WIDTH / 2, HEIGHT / 2};
	i = 0;
	while (i < mip_num)
	{
		image = down_sample_2x(image, resolution);
		image = gaussian_blur(image, \
				(t_vec2f){(int)resolution.x, (int)resolution.y}, blur_size);
		resolution = (t_vec2f){resolution.x / 2, resolution.y / 2};
		i++;
	}
	i = 0;
	resolution = (t_vec2f){resolution.x * 2, resolution.y * 2};
	while (i < mip_num)
	{
		image = up_sample_2x(image, \
				(t_vec2f){(int)resolution.x, (int)resolution.y});
		image = gaussian_blur(image, (t_vec2f){(int)(resolution.x * 2), \
									(int)(resolution.y * 2)}, blur_size);
		resolution = (t_vec2f){resolution.x * 2, resolution.y * 2};
		i++;
	}
	return (image);
}
