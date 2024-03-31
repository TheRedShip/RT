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

int		render_sphere(t_vec2f uv, t_scene *scene, t_sphere *sphere)
{
	// uv.y = 1.0f - uv.y;
	t_vec3f	ray_origin;
	t_vec3f	ray_direction;

	ray_origin = scene->camera->origin;
	ray_direction = (t_vec3f){uv.x, uv.y, -1.0f};

	// sphere : (x - a)² + (y - b)² + (z - c)² - r² = 0
	// segment : (o + dt)
	// equation = (ox + dx * t - a)² + (oy + dy * t - b)² + (oz + dz * t - c)² - r² = 0
	//			= ox² + 2(ox*dx*t) - ox*a + dx²*t² 2(-dx*t*a) - ox*a + a²
	//		a	= (dx² + dy² + dz²)
	//		b	= (2(ox*dx) + 2(-dx*a)) + (2(oy*dy) + 2(-dy*b)) + (2(oz*dz) + 2(-dz*c))
	//		c	= (ox² + 2(-ox*a))

	float	a = vec3f_dot_v(ray_direction, ray_direction);
	float	b = (2*ray_origin.x*ray_direction.x - 2*ray_direction.x*sphere->origin.x) + \
				(2*ray_origin.y*ray_direction.y - 2*ray_direction.y*sphere->origin.y) + \
				(2*ray_origin.z*ray_direction.z - 2*ray_direction.z*sphere->origin.z);
	float	c = (ray_origin.x*ray_origin.x - 2*ray_origin.x*sphere->origin.x + sphere->origin.x*sphere->origin.x) + \
				(ray_origin.y*ray_origin.y - 2*ray_origin.y*sphere->origin.y + sphere->origin.y*sphere->origin.y) + \
				(ray_origin.z*ray_origin.z - 2*ray_origin.z*sphere->origin.z + sphere->origin.z*sphere->origin.z) - \
				(sphere->diameter / 2 * sphere->diameter / 2);
	// equation = (ox + dx * t)² + (oy + dy * t)² + (oz + dz * t)² - r² = 0
	//			= ox² + 2(ox*dx*t) + dx²*t²
	//			+ oy² + 2(oy*dy*t) + dy²*t²
	//			+ oz² + 2(oz*dz*t) + dz²*t² - r² = 0
	// rebuilt	= t²(dx² + dy² + dz²) + t(2(ox*dx + oy*dy + oz*dz)) + (ox² + oy² + oz² - r²) = 0

	// float	a = vec3f_dot_v(ray_direction, ray_direction);
	// float	b = 2.0f * vec3f_dot_v(ray_origin, ray_direction);
	// float	c = vec3f_dot_v(ray_origin, ray_origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	
	float	discriminant = b*b - 4 * a * c;
	
	if (discriminant >= 0.0f)
		return (0xFFFF0000);
	return (0xFF000000);
}

void	render_pixel(t_scene *scene, int x, int y)
{
	t_vec2f		uv;
	t_objects	*objects;

	uv = (t_vec2f){(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
	uv.x = uv.x * 2.0f - 1.0f;
	uv.y = uv.y * 2.0f - 1.0f;

	objects = scene->objects;
	while (objects)
	{
		if (objects->type == OBJ_SPHER)
			put_pixel(scene, x, y, render_sphere(uv, scene, objects->sphere));
		objects = objects->next;
	}
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
			render_pixel(scene, pos.x, pos.y);
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
	printf("Rendering scene : %lu ms\n", get_time() - start);
	return (0);
}