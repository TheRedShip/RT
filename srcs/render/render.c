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

void	calcul_light(t_hitInfo hit_info, t_scene *scene, t_vec3f *light, t_vec3f *contribution, int is_specular)
{
	t_vec3f		light_direction;
	float		diffuse_ratio;

	light_direction = vec3f_sub_v(hit_info.position, scene->lights->origin);
	light_direction = normalize(light_direction);
	diffuse_ratio = vec3f_dot(hit_info.normal, vec3f_mul_f(light_direction, -1.0f));
	if (diffuse_ratio < 0.0f)
		diffuse_ratio = 0.0f;
	if (scene->lights->hard == 1 && scene->lights->ratio > 0.0f)
	{
		t_hitInfo	shadow_hit_info;
		t_ray		ray;
		ray.origin = vec3f_add_v(hit_info.position, vec3f_mul_f(hit_info.normal, 0.0001f));
		ray.direction = vec3f_mul_f(light_direction, -1.0f);
		shadow_hit_info = trace_ray(scene, ray);
		if (shadow_hit_info.distance > 0.0f && shadow_hit_info.distance < vec3f_length(vec3f_sub_v(scene->lights->origin, hit_info.position)))
			diffuse_ratio = 0.0f;
	}
	*light = vec3f_add_v(*light, vec3f_mul_f(scene->lights->color, diffuse_ratio * scene->lights->ratio));
	*light = vec3f_add_v(*light, vec3f_mul_f(hit_info.obj->material.color, hit_info.obj->material.emission_power));
	*contribution = vec3f_mul_v(*contribution, lerp(hit_info.obj->material.color, (t_vec3f){1.0f, 1.0f, 1.0f}, is_specular));
}


t_vec3f		per_pixel(t_scene *scene, t_vec2f uv, t_threads *thread)
{
	t_ray		ray;
	t_hitInfo	hit_info;
	t_vec3f		light;
	t_vec3f 	contribution;
	int			is_specular;

	ray.origin = scene->camera->origin;
	ray.direction = calculate_ray_direction(scene, (t_vec3f){uv.x, uv.y, scene->camera->direction.z});

	light = (t_vec3f){0.0f, 0.0f, 0.0f};
	contribution = (t_vec3f){1.0f, 1.0f, 1.0f};
	int	bounces = 5;
	for (int i = 0; i < (!scene->mouse.is_pressed * (bounces - 2)) + 2; i++)
	{
		hit_info = trace_ray(scene, ray);
		if (hit_info.distance < 0.0f)
		{
			light = vec3f_add_v(light, vec3f_mul_f(scene->ambient_light->color, scene->ambient_light->ratio + scene->mouse.is_pressed));
			break;
		}

		ray = new_ray(hit_info, ray, thread, &is_specular);
		calcul_light(hit_info, scene, &light, &contribution, is_specular);

		if (hit_info.obj->material.emission_power > 0.0f)
			break;
	}
	light = vec3f_mul_v(light, contribution);
	return (light);
}

void	*draw(void *thread_ptr)
{
	t_vec2f		uv;
	t_vec2f		pos;
	t_vec3f		color_acc;
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
			uv = get_uv(pos.x, pos.y);
			scene->mlx->acc_img[(int)pos.y][(int)pos.x] = \
				vec3f_add_v(scene->mlx->acc_img[(int)pos.y][(int)pos.x], per_pixel(scene, uv, thread));

			color_acc = vec3f_div_f(scene->mlx->acc_img[(int)pos.y][(int)pos.x], (float)scene->mlx->frame_index);
			color_acc = clamp(color_acc, 0.0f, 1.0f);
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
		ft_memset(scene->mlx->img.addr, 0, WIDTH * HEIGHT * 4);
	}

	apply_rotationMatrixX(scene->camera->direction.x, scene->camera->rotationMatrixX);
    apply_rotationMatrixY(scene->camera->direction.y, scene->camera->rotationMatrixY);

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