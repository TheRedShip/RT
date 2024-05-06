/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloom.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:36:01 by marvin            #+#    #+#             */
/*   Updated: 2024/05/06 20:10:35 by ycontre          ###   ########.fr       */
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

float	gaussianWeight(float x, float sigma)
{
	return (exp(-(x * x) / (2 * sigma * sigma)) \
			/ (sqrt(2 * M_PI) * sigma));
}

t_vec3f	**gaussianBlur(t_vec3f **image, t_vec2f resolution, int blur_size) {
    int i, j, k, l;
    int kernelMid = blur_size / 2;

    float kernel[blur_size][blur_size];
    float totalWeight = 0.0;
    for (i = 0; i < blur_size; ++i) {
        for (j = 0; j < blur_size; ++j) {
            float distanceX = i - kernelMid;
            float distanceY = j - kernelMid;
            kernel[i][j] = gaussianWeight(sqrt(distanceX * distanceX + distanceY * distanceY), 1);
			totalWeight += kernel[i][j];
        }
    }

    for (i = 0; i < blur_size; ++i) {
        for (j = 0; j < blur_size; ++j) {
            kernel[i][j] /= totalWeight;
        }
    }

	t_vec3f **blurredImage = init_img(NULL, resolution.x, resolution.y);
    for (i = 0; i < resolution.y; ++i) {
        for (j = 0; j < resolution.x; ++j) {
            t_vec3f sum = (t_vec3f){0, 0, 0};
            for (k = -kernelMid; k <= kernelMid; ++k) {
                for (l = -kernelMid; l <= kernelMid; ++l) {
                    int row = i + k;
                    int col = j + l;
                    if (row >= 0 && row < resolution.y && col >= 0 && col < resolution.x)
                        sum = vec3f_add_v(sum, vec3f_mul_f(image[row][col], kernel[k + kernelMid][l + kernelMid]));
				}
            }
            blurredImage[i][j] = sum;
        }
    }
	dup_img(image, blurredImage, resolution);
	ft_free_tab((void **)blurredImage);
	return (image);
}

t_vec3f **sample(t_vec3f **image, int mip_num, int blur_size)
{
	t_vec2f resolution;
	int 	i;

	resolution = (t_vec2f){WIDTH / 2, HEIGHT / 2};
	i = 0;
	while (i < mip_num)
	{
		image = down_sample_2x(image, resolution);
		image = gaussianBlur(image, (t_vec2f){(int)resolution.x, (int)resolution.y}, blur_size); 
		resolution = (t_vec2f){resolution.x / 2, resolution.y / 2};
		i++;
	}
	i = 0;
	resolution = (t_vec2f){resolution.x * 2, resolution.y * 2};
	while (i < mip_num)
	{
		image = up_sample_2x(image, (t_vec2f){(int)resolution.x, (int)resolution.y});
		image = gaussianBlur(image, (t_vec2f){(int)(resolution.x * 2), (int)(resolution.y * 2)}, blur_size); 
		resolution = (t_vec2f){resolution.x * 2, resolution.y * 2};
		i++;
	}
	return (image);
}

t_vec3f	**bloom(t_scene *scene, t_vec3f **image)
{
	if (scene->mlx->is_bloom == 1)
	{
		calcul_treshold(&scene->mlx->postpro_img, image, scene->bloom->treshold);
		scene->mlx->postpro_img = sample(scene->mlx->postpro_img, scene->bloom->mip_num, scene->bloom->blur_size);
		return (add_img(scene->mlx->postpro_img, image));
		// return (scene->mlx->postpro_img);
	}
	else
		return (image);
}