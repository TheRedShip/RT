/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:00:43 by marvin            #+#    #+#             */
/*   Updated: 2024/03/31 00:00:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void   render_pixel(t_scene **scene, int x, int y)
{
	t_vec2f	uv;

	uv = (t_vec2f){(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
	// uv = vec2f_add_f(vec2f_mul_f(uv, 2.0f), -1.0f);
	// uv.x = uv.x * 2.0f - 1.0f;
	// uv.y = uv.y * 2.0f - 1.0f;
	uv.y = 1.0f - uv.y;

	put_pixel(*scene, x, y, 0xFF000000 | ((int)(uv.x * 255.0f) << 16) | ((int)(uv.y * 255.0f) << 8));
}

int		rt_render_scene(t_scene *scene)
{
	u_int64_t	start;
	t_vec2i		pos;

	start = get_time();
	pos.y = 0;
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			render_pixel(&scene, pos.x, pos.y);
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
	printf("Rendering scene : %lu ms\n", get_time() - start);
	return (0);
}