/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloom.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:36:01 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 20:03:56 by ycontre          ###   ########.fr       */
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

t_vec3f **up_sample_2x(t_vec3f **image, t_vec2f resolution)
{
	int		pos[2];
	t_vec3f **tmp;

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
	free(tmp);

	return (image);
}

t_vec3f **boxBlur(t_vec3f **image, t_vec2f resolution) {
    int i, j, k, l;
    int kernelSize = 3; // Taille du noyau de flou
    int kernelMid = kernelSize / 2;
    float kernelValue = 1.0 / (float)(kernelSize * kernelSize); // Normalisation du noyau

	t_vec3f **blurredImage = init_img(NULL, resolution.x, resolution.y);
    // Parcourir chaque pixel de l'image
    for (i = 0; i < resolution.y; ++i) {
        for (j = 0; j < resolution.x; ++j) {
            t_vec3f sum = (t_vec3f){0, 0, 0};
            // Parcourir le voisinage de chaque pixel
            for (k = -kernelMid; k <= kernelMid; ++k) {
                for (l = -kernelMid; l <= kernelMid; ++l) {
                    int row = i + k;
                    int col = j + l;
                    // Vérifier les limites de l'image
                    if (row >= 0 && row < resolution.y && col >= 0 && col < resolution.x) {
                        // Ajouter la valeur du pixel pondérée par la valeur du noyau
                        sum = vec3f_add_v(sum, vec3f_mul_f(image[row][col], kernelValue));
                    }
                }
            }
            // Assigner la somme floutée au pixel correspondant de l'image floutée
            blurredImage[i][j] = sum;
        }
    }
	dup_img(image, blurredImage, resolution);
	free(blurredImage);
	return (image);
}

t_vec3f **box_blur(t_vec3f **image, t_vec2f resolution)
{
	t_vec3f	**tmp;
	int		pos[2];
	int		radius;

	tmp = init_img(NULL, resolution.x, resolution.y);
	radius = 10;

	pos[1] = 0;
	while (pos[1] < resolution.y)
	{
		pos[0] = 0;
		while (pos[0] < resolution.x)
		{
			t_vec3f color = (t_vec3f){0,0,0};
			
			int count = 0;
			int	i = -radius;
			while (i < radius)
			{
				int	j = -radius;
				while (j < radius)
				{
					if (pos[1] + i < 0 || pos[0] + j < 0 || pos[1] + i >= resolution.y || pos[0] + j >= resolution.x)
					{
						j++;
						continue;
					}
					color = vec3f_add_v(color, image[pos[1] + i][pos[0] + j]);		
					j++;
					count++;
				}
				i++;
			}
			color = vec3f_div_f(color, count);
			tmp[pos[1]][pos[0]] = color;

			pos[0]++;
		}
		pos[1]++;
	}
	dup_img(image, tmp, resolution);
	free(tmp);

	return image;
}


t_vec3f **down_sample(t_vec3f **image)
{
	t_vec2f resolution;
	int 	i;
	int		time = 13;

	resolution = (t_vec2f){WIDTH / 2, HEIGHT / 2};
	i = 0;
	while (i < time)
	{
		image = down_sample_2x(image, resolution);
		image = boxBlur(image, (t_vec2f){(int)resolution.x, (int)resolution.y}); 
		resolution = (t_vec2f){resolution.x / 2, resolution.y / 2};
		i++;
	}
	i = 0;
	resolution = (t_vec2f){resolution.x * 2, resolution.y * 2};
	while (i < time)
	{
		image = up_sample_2x(image, (t_vec2f){(int)resolution.x, (int)resolution.y});
		image = boxBlur(image, (t_vec2f){(int)(resolution.x * 2), (int)(resolution.y * 2)}); 
		resolution = (t_vec2f){resolution.x * 2, resolution.y * 2};
		i++;
	}
	printf("resolution %f %f\n", resolution.x, resolution.y);
	return (image);
}

t_vec3f	**bloom(t_scene *scene, t_vec3f **image)
{
	if (scene->mlx->is_bloom == 1)
	{
		calcul_treshold(&scene->mlx->postpro_img, image, 1.0f);
		scene->mlx->postpro_img = down_sample(scene->mlx->postpro_img);
		return (add_img(scene->mlx->postpro_img, image));
		// return (scene->mlx->postpro_img);
	}
	else
		return (image);
}