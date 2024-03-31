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
	uv.x = uv.x * 2.0f - 1.0f;
	uv.y = uv.y * 2.0f - 1.0f;
	// uv.y = 1.0f - uv.y;

	// sphere : (x - a)² + (y - b)² + (z - c)² - r² = 0
	// segment : (o + dt)
	// equation = (ox + dx * t - a)² + (oy + dy * t - b)² + (oz + dz * t - c)² - r² = 0
	//			= ox² + ox*dx*t - ox*a + dx*t*ox + dx²*t² - dx*t*a - a*ox - a*dx*t + a²
	//			= ox² + 2(ox*dx*t) - 2(ox*a) + dx²*t² - 2(dx*t*a) - a²
	// rebuilt	= (dx² + dy² + dz²)*t² + ((2*ox*dx - 2*dx*a) + (2*oy*dy - 2*dy*a) + (2*oz*dz - 2*dz*a))*t
	//			+ ((ox² + 2*ox*a - a²) + (oy² + 2*oy*a - a²) + (oz² + 2*oz*a - a²) - r²) = 0 
	//
	// equation = (ox + dx * t)² + (oy + dy * t)² + (oz + dz * t)² - r² = 0
	//			= ox² + 2(ox*dx*t) + dx²*t²
	//			+ oy² + 2(oy*dy*t) + dy²*t²
	//			+ oz² + 2(oz*dz*t) + dz²*t² - r² = 0
	// rebuilt	= t²(dx² + dy² + dz²) + t(2(ox*dx + oy*dy + oz*dz)) + (ox² + oy² + oz² - r²) = 0

	t_vec3f	ray_origin;
	t_vec3f	ray_direction;
	float	sphere_radius;

	ray_origin = (t_vec3f){0.0f, 0.0f, 2.0f};
	ray_direction = (t_vec3f){uv.x, uv.y, -1.0f};
	sphere_radius = 0.5f;

	float	a = vec3f_dot_v(ray_direction, ray_direction);
	float	b = 2.0f * vec3f_dot_v(ray_origin, ray_direction);
	float	c = vec3f_dot_v(ray_origin, ray_origin) - sphere_radius * sphere_radius;
	
	float	discriminant = b*b - 4 * a * c;
	
	if (discriminant >= 0.0f)
		put_pixel(*scene, x, y, 0xFFFF0000);

	
	//t = hit_distance

	// put_pixel(*scene, x, y, 0xFF000000 | ((int)(uv.x * 255.0f) << 16) | ((int)(uv.y * 255.0f) << 8));
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