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
	t_vec3f light_direction;

	ray_origin = scene->camera->origin;
	ray_direction = (t_vec3f){uv.x, uv.y, -1.0f};

	light_direction = scene->lights->origin;
	light_direction = normalize(light_direction);

	// float	a = vec3f_dot_v(ray_direction, ray_direction);
	// float	b = (2*ray_origin.x*ray_direction.x - 2*ray_direction.x*sphere->origin.x) + 
	// 			(2*ray_origin.y*ray_direction.y - 2*ray_direction.y*sphere->origin.y) + 
	// 			(2*ray_origin.z*ray_direction.z - 2*ray_direction.z*sphere->origin.z);
	// float	c = (ray_origin.x*ray_origin.x - 2*ray_origin.x*sphere->origin.x + sphere->origin.x*sphere->origin.x) + 
	// 			(ray_origin.y*ray_origin.y - 2*ray_origin.y*sphere->origin.y + sphere->origin.y*sphere->origin.y) + 
	// 			(ray_origin.z*ray_origin.z - 2*ray_origin.z*sphere->origin.z + sphere->origin.z*sphere->origin.z) - 
	// 			(sphere->diameter / 2 * sphere->diameter / 2);

	float	a = vec3f_dot_v(ray_direction, ray_direction);
	float	b = 2.0f * vec3f_dot_v(ray_origin, ray_direction);
	float	c = vec3f_dot_v(ray_origin, ray_origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	
	float	discriminant = b*b - 4.0f * a * c;
	
	if (discriminant >= 0.0f)
	{
		float t[2];

		t[0] = (-b - sqrtf(discriminant)) / (2.0f * a);
		t[1] = (-b + sqrtf(discriminant)) / (2.0f * a);

		for (int i = 0; i < 2; i++)
		{
			t_vec3f hitPosition = {ray_origin.x + ray_direction.x * t[i], \
									ray_origin.y + ray_direction.y * t[i], \
									ray_origin.z + ray_direction.z * t[i]};
			t_vec3f normal = vec3f_sub_v(hitPosition, sphere->origin);
			normal = normalize(normal);

			float light = vec3f_dot_v(normal, vec3f_mul_f(light_direction, -1.0f));

			if (light < 0.0f)
				light = 0.0f;
			return (rgb_to_hex(vec3f_mul_f(sphere->color, light)));
		}
	}
	return (0xFF000000);
}

void	render_pixel(t_scene *scene, int x, int y)
{
	t_vec2f		uv;
	t_objects	*objects;
	float		aspect_ratio;

	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	uv = (t_vec2f){(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
	uv.x = uv.x * 2.0f - 1.0f;
	uv.y = uv.y * 2.0f - 1.0f;
	uv.x *= aspect_ratio;

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
	t_vec2f		pos;

	//
	static float	t = 0.0f;
	t+=0.03;

	scene->lights->origin.x += cos(t) * 1.5f;
	scene->lights->origin.y += sin(t) * 1.5f;
	//

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