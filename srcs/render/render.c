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

float calc_t_sphere(t_ray ray, t_objects *obj, t_sphere *sphere)
{
	// ray.origin = vec3f_sub_v(ray.origin, obj->origin);

	float	a = vec3f_dot_v(ray.direction, ray.direction);
	float	b = (2*ray.origin.x*ray.direction.x - 2*ray.direction.x*obj->origin.x) + 
				(2*ray.origin.y*ray.direction.y - 2*ray.direction.y*obj->origin.y) + 
				(2*ray.origin.z*ray.direction.z - 2*ray.direction.z*obj->origin.z);
	float	c = (ray.origin.x*ray.origin.x - 2*ray.origin.x*obj->origin.x + obj->origin.x*obj->origin.x) + 
				(ray.origin.y*ray.origin.y - 2*ray.origin.y*obj->origin.y + obj->origin.y*obj->origin.y) + 
				(ray.origin.z*ray.origin.z - 2*ray.origin.z*obj->origin.z + obj->origin.z*obj->origin.z) - 
				(sphere->diameter / 2 * sphere->diameter / 2);

	// float	a = vec3f_dot_v(ray.direction, ray.direction);
	// float	b = 2.0f * vec3f_dot_v(ray.origin, ray.direction);
	// float	c = vec3f_dot_v(ray.origin, ray.origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	
	float	discriminant = b*b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return -1.0f;
	return (-b - sqrtf(discriminant)) / (2.0f * a);
}

float	calc_t_object(t_ray ray, t_objects *obj)
{
	if (obj->type == OBJ_SPHER)
		return (calc_t_sphere(ray, obj, obj->sphere));
	return (-1.0f);
}

t_hitInfo	miss_ray(t_ray ray)
{
	t_hitInfo	hit_info;

	(void) ray;
	hit_info.distance = -1.0f;
	return (hit_info);
}

t_hitInfo	hit_ray(t_ray ray, t_objects *obj, float t)
{
	t_hitInfo	hit_info;

	hit_info.distance = t;
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, t));
	hit_info.normal = normalize(vec3f_sub_v(hit_info.position, obj->origin));
	hit_info.obj = obj;
	return (hit_info);
}

t_hitInfo	trace_ray(t_scene *scene, t_ray ray)
{
	float		temp_dist;
	float		closest_dist;
	t_objects	*temp_object;
	t_objects	*closest_obj;

	temp_object = scene->objects;
	closest_obj = NULL;
	closest_dist = -1.0f;
	while (temp_object)
	{
		temp_dist = calc_t_object(ray, temp_object);
		if (temp_dist > 0.0f && (temp_dist < closest_dist || closest_obj == NULL))
		{
			closest_dist = temp_dist;
			closest_obj = temp_object;
		}
		temp_object = temp_object->next;
	}

	if (closest_dist == -1.0f)
		return (miss_ray(ray));
	return (hit_ray(ray, closest_obj, closest_dist));
}

t_vec3f		per_pixel(t_scene *scene, int x, int y)
{
	t_vec2f		uv;
	float		aspect_ratio;
	t_ray		ray;
	t_hitInfo	hit_info;

	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	uv = (t_vec2f){(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
	uv.x = uv.x * 2.0f - 1.0f;
	uv.y = uv.y * 2.0f - 1.0f;
	uv.y = -uv.y;
	uv.x *= aspect_ratio;

	ray.origin = scene->camera->origin;
	ray.direction = (t_vec3f){uv.x, uv.y, -1.0f};
	
	float	light;
	t_vec3f	color;

	color = (t_vec3f){0.0f, 0.0f, 0.0f};
	float multiplier = 1.0f;
	for (int i = 0; i < 4; i++)
	{
		hit_info = trace_ray(scene, ray);
		if (hit_info.distance < 0.0f)
			break;

		t_vec3f	light_direction = vec3f_sub_v(hit_info.position, scene->lights->origin);
		light_direction = normalize(light_direction);

		light = vec3f_dot_v(hit_info.normal, vec3f_mul_f(light_direction, -1.0f));
		if (light < 0.0f)
			light = 0.0f;
		
		color = vec3f_add_v(color, vec3f_mul_f(vec3f_mul_f(hit_info.obj->color, light), multiplier));
		multiplier *= 0.75f;

		ray.origin = vec3f_add_v(hit_info.position, vec3f_mul_f(hit_info.normal, 0.0001f));
		ray.direction = vec3f_sub_v(ray.direction, vec3f_mul_f(hit_info.normal, 2 * vec3f_dot_v(ray.direction, hit_info.normal)));
		// r.d = r.d - 2.0f * dot(r.d, h.normal) * h.normal;
	}
	return (color);
}

int		rt_render_scene(t_scene *scene)
{
	u_int64_t	start;
	t_vec2f		pos;
	t_vec3f		color;
	
	start = get_time();
	pos.y = 0;
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			color = per_pixel(scene, pos.x, pos.y);
			color = clamp(color, 0.0f, 1.0f);
			color = vec3f_mul_f(color, 255.0f);
			put_pixel(scene, pos.x, pos.y, rgb_to_hex(color));
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
	printf("Rendering scene : %lu ms\n", get_time() - start);
	return (0);
}