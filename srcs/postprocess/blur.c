/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:29:10 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 00:29:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	gaussian_weight(float x, float sigma)
{
	return (exp(-(x * x) / (2 * sigma * sigma)) \
			/ (sqrt(2 * M_PI) * sigma));
}

t_vec3f	**gaussian_blur(t_vec3f **image, t_vec2f resolution, int blur_size)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		kernel_mid = blur_size / 2;
	float	kernel[blur_size][blur_size];
	float	total_weight = 0.0;

	i = 0;
	while (i < blur_size)
	{
		j = 0;
		while (j < blur_size)
		{
			float distanceX = i - kernel_mid;
			float distanceY = j - kernel_mid;
			kernel[i][j] = gaussian_weight(sqrt(distanceX * distanceX + \
							distanceY * distanceY), 1);
			total_weight += kernel[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < blur_size)
	{
		j = 0;
		while (j < blur_size)
		{
			kernel[i][j] /= total_weight;
			j++;
		}
		i++;
	}

	t_vec3f **blurredImage = init_img(NULL, resolution.x, resolution.y);
	i = 0;
	while (i < resolution.y)
	{
		j = 0;
		while (j < resolution.x)
		{
			t_vec3f sum = (t_vec3f){0, 0, 0};
			k = -kernel_mid;
			while (k <= kernel_mid)
			{
				l = -kernel_mid;
				while (l <= kernel_mid)
				{
					int row = i + k;
					int col = j + l;
					if (row >= 0 && row < resolution.y && col >= 0 && col < resolution.x)
						sum = vec3f_add_v(sum, vec3f_mul_f(image[row][col], kernel[k + kernel_mid][l + kernel_mid]));
					l++;
				}
				k++;
			}
			blurredImage[i][j] = sum;
			j++;
		}
		i++;
	}
	dup_img(image, blurredImage, resolution);
	ft_free_tab((void **)blurredImage);
	return (image);
}