/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:19:17 by marvin            #+#    #+#             */
/*   Updated: 2024/03/30 14:19:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_window(t_scene **scene)
{
	(*scene)->mlx->mlx = mlx_init();
	if (!(*scene)->mlx->mlx)
		rt_free_scene(*scene);
	(*scene)->mlx->win = mlx_new_window((*scene)->mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!(*scene)->mlx->win)
		rt_free_scene(*scene);
	(*scene)->mlx->img.img = mlx_new_image((*scene)->mlx->mlx, WIDTH, HEIGHT);
	(*scene)->mlx->img.addr = mlx_get_data_addr((*scene)->mlx->img.img, &(*scene)->mlx->img.bits_per_pixel, \
												&(*scene)->mlx->img.line_length, &(*scene)->mlx->img.endian);
}

void	put_pixel(t_scene *scene, int x, int y, int color)
{
	t_data *data;
	char	*dst;

	data = &scene->mlx->img;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
