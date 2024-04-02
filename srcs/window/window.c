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
	// (*scene)->mlx->acc_img.img = mlx_new_image((*scene)->mlx->mlx, WIDTH, HEIGHT);
	// (*scene)->mlx->acc_img.addr = mlx_get_data_addr((*scene)->mlx->acc_img.img, &(*scene)->mlx->acc_img.bits_per_pixel,
												// &(*scene)->mlx->acc_img.line_length, &(*scene)->mlx->acc_img.endian);
}

void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
