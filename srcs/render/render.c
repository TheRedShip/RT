/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:00:43 by marvin            #+#    #+#             */
/*   Updated: 2024/04/30 19:57:58 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		if (temp_hit.distance > 0.0f && (temp_hit.distance < closest_hit.distance || closest_hit.distance < 0.0f))
		{
			closest_hit = temp_hit;
			closest_hit.obj = temp_object;
		}
		temp_object = temp_object->next;
	}
	if (closest_hit.distance == -1.0f)
		return (closest_hit);
	if (closest_hit.obj->type == OBJ_PORTAL)
		ray = portal_ray(scene, &closest_hit, ray);
	return (closest_hit);
}

t_vec3f		per_pixel(t_scene *scene, t_vec2f uv, t_threads *thread)
{
	t_ray		ray;
	t_hitInfo	hit_info;
	t_vec3f		light;
	t_vec3f 	contribution;
	int			is_specular;

	ray.origin = scene->camera->origin;
	ray.direction = calculate_ray_direction(scene, (t_vec3f){uv.x, uv.y, -1});

	light = (t_vec3f){0.0f, 0.0f, 0.0f};
	contribution = (t_vec3f){1.0f, 1.0f, 1.0f};
	for (int i = 0; i < (!scene->mouse.is_pressed * (scene->camera->bounce - 2)) + 2; i++)
	{
		hit_info = trace_ray(scene, ray);
		if (hit_info.distance < 0.0f)
		{
			light = vec3f_add_v(light, vec3f_mul_f(scene->ambient_light->color, scene->ambient_light->ratio));
			break;
		}
		ray = new_ray(hit_info, ray, thread, &is_specular);
		calcul_light(hit_info, scene, &light, &contribution, is_specular);
		if (hit_info.obj->material.emission_power > 0.0f)
			break;
	}
	return (vec3f_mul_v(light, contribution));
}

void	*draw(void *thread_ptr)
{
	int			pos[2];
	t_vec2f		uv;
	t_scene		*scene;
	t_threads	*thread;

	thread = (t_threads *)thread_ptr;
	scene = thread->scene;
	pos[1] = thread->id;
	while (pos[1] < HEIGHT)
	{
		pos[0] = 0;
		while (pos[0] < WIDTH)
		{
			if (scene->mlx->antialiasing)
				uv = get_uv(pos[0] + (float)(ft_random(thread->id, -1, 1)), pos[1] + (float)(ft_random(thread->id, -1, 1)));
			else
				uv = get_uv(pos[0], pos[1]);
			scene->mlx->acc_img[pos[1]][pos[0]] = \
				vec3f_add_v(scene->mlx->acc_img[pos[1]][pos[0]], per_pixel(scene, uv, thread));
			scene->mlx->final_img[pos[1]][pos[0]] = \
				vec3f_div_f(scene->mlx->acc_img[pos[1]][pos[0]], (float)scene->mlx->frame_index);
			pos[0]++;
		}
		pos[1] += THREADS;
	}
	return (NULL);
}

void	rt_render_image(t_vec3f **image, t_data *img)
{
	t_vec3f	color;
	t_vec2f	pos;

	pos.y = 0;
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			color = image[(int)pos.y][(int)pos.x];
			color = clamp(color, 0.0f, 1.0f);
			put_pixel(img, pos.x, pos.y, rgb_to_hex(color));
			pos.x++;
		}
		pos.y++;
	}
}

int		rt_render_scene(t_scene *scene)
{
	u_int64_t		start;
	t_threads		threads[THREADS];

	if (scene->mlx->frame_index == 1)
	{
		ft_free_tab((void **)(scene->mlx->acc_img));
		scene->mlx->acc_img = init_img(scene, WIDTH, HEIGHT);
		if(!scene->server.ip)
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
	if(!scene->server.ip)
		rt_render_image(bloom(scene, scene->mlx->final_img), &scene->mlx->img);
	if(scene->server.ip)
	{
		if(!send_map(scene, scene->mlx->acc_img)) 
			scene->server.error = 1;
	}
	else
		mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
	printf("Rendering scene : %lu ms %d            \r", get_time() - start, scene->mlx->frame_index);
	fflush(stdout);
	if (scene->mlx->is_acc)
		scene->mlx->frame_index++;
	else
		scene->mlx->frame_index = 1;
	return (0);
}
