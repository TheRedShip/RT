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

t_hitInfo	hit_sphere(t_ray ray, t_objects *obj, t_sphere *sphere)
{
	float		a;
	float		b;
	float		c;
	t_hitInfo	hit_info;
	float		discriminant;
	a = vec3f_dot_v(ray.direction, ray.direction);
	b = (2*ray.origin.x*ray.direction.x - 2*ray.direction.x*obj->origin.x) + 
				(2*ray.origin.y*ray.direction.y - 2*ray.direction.y*obj->origin.y) + 
				(2*ray.origin.z*ray.direction.z - 2*ray.direction.z*obj->origin.z);
	c = (ray.origin.x*ray.origin.x - 2*ray.origin.x*obj->origin.x + obj->origin.x*obj->origin.x) + 
				(ray.origin.y*ray.origin.y - 2*ray.origin.y*obj->origin.y + obj->origin.y*obj->origin.y) + 
				(ray.origin.z*ray.origin.z - 2*ray.origin.z*obj->origin.z + obj->origin.z*obj->origin.z) - 
				(sphere->diameter / 2 * sphere->diameter / 2);
	//a = vec3f_dot_v(ray.direction, ray.direction);
	//b = 2.0f * vec3f_dot_v(ray.origin, ray.direction);
	//c = vec3f_dot_v(ray.origin, ray.origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	
	discriminant = b*b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		hit_info.distance = -1.0f;
		return (hit_info);
	}
	hit_info.distance = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (hit_info.distance < 0.0f)
		hit_info.distance = (-b + sqrtf(discriminant)) / (2.0f * a);
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, hit_info.distance));
	hit_info.normal = normalize(vec3f_sub_v(hit_info.position, obj->origin));
	return (hit_info);
}

t_hitInfo		hit_plane(t_ray ray, t_objects *obj, t_plane *plane)
{
	t_hitInfo	hit_info;
	float		denom;

	denom = vec3f_dot_v(plane->normal, ray.direction);
	if (denom == 0)
	{
		hit_info.distance = -1.0f;
		return (hit_info);
	} 
	hit_info.distance = vec3f_dot_v(vec3f_sub_v(obj->origin, ray.origin), plane->normal) / denom;
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, hit_info.distance));
	hit_info.normal = plane->normal;
	return (hit_info);
}

t_hitInfo		hit_objects(t_ray ray, t_objects *obj)
{
	t_hitInfo	hit_info;

	if (obj->type == OBJ_SPHER)
		return (hit_sphere(ray, obj, obj->sphere));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane(ray, obj, obj->plane));
	hit_info.distance = -1.0f;
	return (hit_info);
}

t_hitInfo	trace_ray(t_scene *scene, t_ray ray)
{
	t_hitInfo	temp_hit;
	t_objects	*temp_object;
	t_hitInfo	closest_hit;

	temp_object = scene->objects;
	closest_hit.distance = -1.0f;
	while (temp_object)
	{
		temp_hit = hit_objects(ray, temp_object);
		if (temp_hit.distance > 0.0f && (temp_hit.distance < closest_hit.distance || closest_hit.distance == -1.0f))
		{
			closest_hit = temp_hit;
			closest_hit.obj = temp_object;
		}
		temp_object = temp_object->next;
	}
	if (closest_hit.distance == -1.0f)
		return (closest_hit);
	return (closest_hit);
}

t_vec3f		per_pixel(t_scene *scene, int x, int y, t_threads *thread)
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
	ray.direction = calculate_ray_direction(scene, (t_vec3f){uv.x, uv.y, -1.0f});

	t_vec3f	light;
	t_vec3f contribution;

	light = vec3f_mul_f(scene->ambient_light->color, scene->ambient_light->ratio);
	contribution = (t_vec3f){1.0f, 1.0f, 1.0f};
	int	bounces = 5;
	for (int i = 0; i < (!scene->mouse.is_pressed * (bounces - 2)) + 2; i++)
	{
		hit_info = trace_ray(scene, ray);
		if (hit_info.distance < 0.0f)
			break;

		t_vec3f	light_direction = vec3f_sub_v(hit_info.position, scene->lights->origin);
		light_direction = normalize(light_direction);

		float diffuse_ratio = vec3f_dot_v(hit_info.normal, vec3f_mul_f(light_direction, -1.0f));
		if (diffuse_ratio < 0.0f)
			diffuse_ratio = 0.0f;
		
		light = vec3f_add_v(light, vec3f_mul_f(scene->lights->color, diffuse_ratio * scene->lights->ratio));
		contribution = vec3f_mul_v(contribution, hit_info.obj->material.color);
		light = vec3f_add_v(light, vec3f_mul_f(hit_info.obj->material.color, hit_info.obj->material.emission_power));

		float min = -1.0f;
		float max = 1.0f;

		float roughness_x = min + (float)(ft_random(thread->id)) / (float)(2147483647) * (max - min);
		float roughness_y = min + (float)(ft_random(thread->id)) / (float)(2147483647) * (max - min);
		float roughness_z = min + (float)(ft_random(thread->id)) / (float)(2147483647) * (max - min);
		t_vec3f in_unit_sphere = normalize((t_vec3f){roughness_x, roughness_y, roughness_z});
		ray.direction = reflect(ray.direction, vec3f_add_v(hit_info.normal, 
				vec3f_mul_f(in_unit_sphere, hit_info.obj->material.roughness)));
		// ray.direction = normalize(vec3f_add_v(hit_info.normal, in_unit_sphere));
		// ray.direction = normalize(vec3f_add_v(hit_info.normal, vec3f_mul_f(in_unit_sphere, hit_info.obj->material.roughness)));
		
		ray.origin = vec3f_add_v(hit_info.position, vec3f_mul_f(hit_info.normal, 0.0001f));
	}
	light = vec3f_mul_v(light, contribution);
	return (light);
}

void	*draw(void *thread_ptr)
{
	t_vec2f		pos;
	t_vec3f		color;
	t_scene		*scene;
	t_threads	*thread;

	thread = (t_threads *)thread_ptr;
	scene = thread->scene;
	pos.y = thread->id;
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			color = per_pixel(scene, pos.x, pos.y, thread);

			scene->mlx->acc_img[(int)pos.y][(int)pos.x] = \
				vec3f_add_v(scene->mlx->acc_img[(int)pos.y][(int)pos.x], color);

			t_vec3f color_acc = vec3f_div_f(scene->mlx->acc_img[(int)pos.y][(int)pos.x], (float)scene->mlx->frame_index);
			color_acc = clamp(color_acc, 0.0f, 1.0f);
			color_acc = vec3f_mul_f(color_acc, 255.0f);
			put_pixel(&scene->mlx->img, pos.x, pos.y, rgb_to_hex(color_acc));
			pos.x++;
		}
		pos.y += THREADS;
	}
	return (NULL);
}

int		rt_render_scene(t_scene *scene)
{
	u_int64_t		start;
	t_threads		threads[THREADS];

	if (scene->mlx->frame_index == 1)
	{
		ft_free_tab((void **)(scene->mlx->acc_img));
		scene->mlx->acc_img = init_acc_img(scene);
	}

	start = get_time();
	for(int i = 0; i < THREADS; i++)
	{
		threads[i].id = i;
		threads[i].scene = scene;
		pthread_create(&(threads[i].thread), NULL, draw, (threads + i));
	}
	for(int i = 0; i < THREADS; i++)
		pthread_join(threads[i].thread, NULL);
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
	printf("Rendering scene : %lu ms %d\n", get_time() - start, scene->mlx->frame_index);
	if (scene->mlx->is_acc)
		scene->mlx->frame_index++;
	else
		scene->mlx->frame_index = 1;
	return (0);
}