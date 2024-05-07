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

t_vec3f	apply_gaussian(int t[5], t_vec2f r, \
				t_vec3f **im, float ke[10][10])
{
	t_vec3f	s;

	s = (t_vec3f){0, 0, 0};
	while (++t[2] <= t[4])
	{
		t[3] = -t[4] - 1;
		while (++t[3] <= t[4])
			if (t[0] + t[2] >= 0 && t[0] + t[2] < r.y \
					&& t[1] + t[3] >= 0 \
					&& t[1] + t[3] < r.x)
				s = v_add_v(s, v_mul_f(im[t[0] + t[2]][t[1] + t[3]], \
						ke[t[2] + t[4]][t[3] + t[4]]));
	}
	return (s);
}

t_vec3f	**gaussian_blur(t_vec3f **im, t_vec2f res, int blur_size)
{
	float	ke[10][10];
	int		tab[5];
	t_vec3f	**blurred_im;

	tab[4] = blur_size / 2;
	fill_kernel(blur_size, ke);
	blurred_im = init_img(NULL, res.x, res.y);
	tab[0] = -1;
	while (++tab[0] < res.y)
	{
		tab[1] = -1;
		while (++tab[1] < res.x)
		{
			tab[2] = -tab[4] - 1;
			blurred_im[tab[0]][tab[1]] = apply_gaussian(tab, res, im, ke);
		}
	}
	dup_img(im, blurred_im, res);
	ft_free_tab((void **)blurred_im);
	return (im);
}
