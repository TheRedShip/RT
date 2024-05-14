/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:19:17 by marvin            #+#    #+#             */
/*   Updated: 2024/05/02 19:01:49 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_window(t_scene *scene, int headless)
{
	scene->mlx->mlx = mlx_init();
	if (!scene->mlx->mlx)
		rt_free_scene(scene, 1);
	if (!headless)
		scene->mlx->win = mlx_new_window(scene->mlx->mlx, \
			WIDTH, HEIGHT, "miniRT");
	if (!headless && !scene->mlx->win)
		rt_free_scene(scene, 1);
	scene->mlx->img.img = mlx_new_image(scene->mlx->mlx, WIDTH, HEIGHT);
	scene->mlx->img.addr = mlx_get_data_addr(scene->mlx->img.img, \
				&scene->mlx->img.bpp, &scene->mlx->img.size, \
				&scene->mlx->img.endian);
}

void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_data *img, int x, int y)
{
	return (*(unsigned int *)(img->addr + \
		(y * img->size + x * (img->bpp / 8))));
}
