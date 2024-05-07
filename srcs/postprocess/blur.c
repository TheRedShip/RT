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

void	fill_kernel(int blur_size, float kernel[10][10])
{
	int		i;
	int		j;
	int		k;
	float	total_weight;

	total_weight = 0.0;
	k = blur_size / 2;
	i = -1;
	while (++i < blur_size)
	{
		j = -1;
		while (++j < blur_size)
		{
			kernel[i][j] = gaussian_weight(sqrt(\
					(i - k) * (i - k) + (j - k) * (j - k)), 1);
			total_weight += kernel[i][j];
		}
	}
	i = -1;
	while (++i < blur_size)
	{
		j = -1;
		while (++j < blur_size)
			kernel[i][j] /= total_weight;
	}
}

t_vec3f	**gaussian_blur(t_vec3f **im, t_vec2f resolution, int blur_size)
{
	int		k_m;
	float	ke[10][10];
	int		tab[4];
	t_vec3f	**blurred_im;
	t_vec3f	s;

	k_m = blur_size / 2;
	fill_kernel(blur_size, ke);
	blurred_im = init_img(NULL, resolution.x, resolution.y);
	tab[0] = -1;
	while (++tab[0] < resolution.y)
	{
		tab[1] = -1;
		while (++tab[1] < resolution.x)
		{
			s = (t_vec3f){0, 0, 0};
			tab[2] = -k_m - 1;
			while (++tab[2] <= k_m)
			{
				tab[3] = -k_m - 1;
				while (++tab[3] <= k_m)
					if (tab[0] + tab[2] >= 0 && tab[0] + tab[2] < resolution.y && tab[1] + tab[3] >= 0 \
							&& tab[1] + tab[3] < resolution.x)
						s = v_add_v(s, v_mul_f(im[tab[0] + tab[2]][tab[1] + tab[3]], ke[tab[2] + k_m][tab[3] + k_m]));
			}
			blurred_im[tab[0]][tab[1]] = s;
		}
	}
	dup_img(im, blurred_im, resolution);
	ft_free_tab((void **)blurred_im);
	return (im);
}
