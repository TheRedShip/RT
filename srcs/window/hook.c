/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:12:28 by marvin            #+#    #+#             */
/*   Updated: 2024/04/09 01:04:38 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_scene *scene)
{
	int	moved;

	moved = key_move_hook(keycode, scene);
	key_settings_hook(keycode, scene);
	if (keycode == KEY_ESCH)
		rt_free_scene(scene, 1);
	if (moved)
		scene->mlx->frame_index = 1;
	return (0);
}

int	mouse_hook_move(int x, int y, t_scene *scene)
{
	t_vec3f	mouse_delta;

	if (scene->mouse.is_pressed)
	{
		mouse_delta.x = x - scene->mouse.pos.x;
		mouse_delta.y = y - scene->mouse.pos.y;
		scene->camera->direction.y += mouse_delta.x * 0.002f;
		scene->camera->direction.x -= mouse_delta.y * 0.002f;
		scene->mlx->frame_index = 1;
	}
	scene->mouse.pos.x = x;
	scene->mouse.pos.y = y;
	return (0);
}

int	mouse_hook_press(int button, int x, int y, t_scene *scene)
{
	t_vec2f		uv;
	t_ray		ray;
	t_hit_info	hit_info;

	if (button == 3)
	{
		scene->mlx->frame_index = 1;
		scene->mouse.is_pressed = 1;
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
	return (0);
}

int	mouse_hook_release(int button, int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	if (button == 3)
	{
		scene->mlx->frame_index = 1;
		scene->mouse.is_pressed = 0;
	}
	return (0);
}
