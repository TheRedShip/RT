/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:16:19 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/12 22:21:47 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	server_key_hook(int key, void *data)
{
	t_scene	*scene;

	scene = data;
	pthread_mutex_lock(&scene->server.mutex);
	if (key_move_hook(key, scene))
	{
		scene->mlx->frame_index = 1;
		reset_img(scene->mlx->acc_img);
	}
	if (key == KEY_ESCH)
		scene->server.stop = 1;
	if (key == KEY_BLOOM)
		scene->mlx->is_bloom = !scene->mlx->is_bloom;
	if (key == KEY_ENTER)
	{
		scene->mlx->is_acc = !scene->mlx->is_acc;
		printf("accumulation : %d\n", scene->mlx->is_acc);
		scene->mlx->frame_index = 1 + scene->mlx->is_acc;
	}
	if (key == 65451)
		scene->bloom->mip_num++;
	if (key == 65453)
		scene->bloom->mip_num--;
	pthread_mutex_unlock(&scene->server.mutex);
	return (0);
}

int	server_loop_hook(void *data)
{
	t_scene	*scene;

	scene = data;
	if (get_stopped(scene))
	{
		mlx_loop_end(scene->mlx->mlx);
		return (0);
	}
	pthread_mutex_lock(&scene->server.mutex);
	apply_rotation_matrix_x(scene->camera->direction.x,
		scene->camera->rotation_matrix_x);
	apply_rotation_matrix_y(scene->camera->direction.y,
		scene->camera->rotation_matrix_y);
	rt_render_image(scene, bloom(scene, scene->mlx->final_img));
	pthread_mutex_unlock(&scene->server.mutex);
	usleep(1000 * 100);
	return (0);
}

int	mouse_hook_press_server(int button, int x, int y, t_scene *scene)
{
	t_vec2f		uv;
	t_ray		ray;
	t_hit_info	hit_info;

	pthread_mutex_lock(&scene->server.mutex);
	if (button == 3)
	{
		scene->mlx->frame_index = 1;
		scene->mouse.is_pressed = 1;
		reset_img(scene->mlx->acc_img);
	}
	else if (button == 1)
	{
		uv = get_uv(NULL, x, y);
		ray.origin = scene->camera->origin;
		ray.direction = calculate_ray_direction(scene, \
					(t_vec3f){uv.x, uv.y, scene->camera->direction.z});
		hit_info = trace_ray(scene, ray);
		(void) hit_info;
	}
	pthread_mutex_unlock(&scene->server.mutex);
	return (0);
}

int	mouse_hook_release_server(int button, int x, int y, t_scene *scene)
{
	(void) x;
	(void) y;
	if (button == 3)
	{
		pthread_mutex_lock(&scene->server.mutex);
		scene->mlx->frame_index = 1;
		scene->mouse.is_pressed = 0;
		reset_img(scene->mlx->acc_img);
		pthread_mutex_unlock(&scene->server.mutex);
	}
	return (0);
}

int	mouse_hook_move_server(int x, int y, t_scene *scene)
{
	t_vec3f	mouse_delta;

	if (scene->mouse.is_pressed)
	{
		pthread_mutex_lock(&scene->server.mutex);
		mouse_delta.x = x - scene->mouse.pos.x;
		mouse_delta.y = y - scene->mouse.pos.y;
		scene->camera->direction.y += mouse_delta.x * 0.002f;
		scene->camera->direction.x -= mouse_delta.y * 0.002f;
		scene->mlx->frame_index = 1;
		reset_img(scene->mlx->acc_img);
		pthread_mutex_unlock(&scene->server.mutex);
	}
	scene->mouse.pos.x = x;
	scene->mouse.pos.y = y;
	return (0);
}
