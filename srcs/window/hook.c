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

void	move_camera(t_scene *scene, t_vec3f movement)
{
	t_vec3f	rotate_movement;

	multiply_matrix_vector(scene->camera->rotation_matrix_x, \
							movement, &rotate_movement);
	multiply_matrix_vector(scene->camera->rotation_matrix_y, \
					rotate_movement, &rotate_movement);
	scene->camera->origin = v_add_v(scene->camera->origin, \
				rotate_movement);
}

int		key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_FORW)
		move_camera(scene, (t_vec3f){0, 0, -0.15f});
	else if (keycode == KEY_BACK)
		move_camera(scene, (t_vec3f){0, 0, 0.15f});
	else if (keycode == KEY_LEFT)
		move_camera(scene, (t_vec3f){-0.15f, 0, 0});
	else if (keycode == KEY_RIGHT)
		move_camera(scene, (t_vec3f){0.15f, 0, 0});
	else if (keycode == KEY_UPE)
		move_camera(scene, (t_vec3f){0, 0.15f, 0});
	else if (keycode == KEY_DOWNA)
		move_camera(scene, (t_vec3f){0, -0.15f, 0});
	else if (keycode == KEY_ESCH)
		rt_free_scene(scene, 1);
	else if (keycode == KEY_ENTER)
	{
		scene->mlx->is_acc = !scene->mlx->is_acc;
		printf("miniRT : accumulating %d      \n", scene->mlx->is_acc);
	}
	else if (keycode == KEY_ALIA)
	{
		scene->mlx->antialiasing = !scene->mlx->antialiasing;
		printf("miniRT : antialiasing %d      \n", scene->mlx->antialiasing);
	}
	else if (keycode == KEY_BLOOM)
	{
		scene->mlx->is_bloom = !scene->mlx->is_bloom;
		printf("miniRT : bloom %d             \n", scene->mlx->is_bloom);
	}
	else if (keycode == 65451)
		scene->bloom->mip_num++;
	else if (keycode == 65453)
		scene->bloom->mip_num--;
	if (keycode < 65000 && keycode != KEY_BLOOM)
		scene->mlx->frame_index = 1;
	return (0);
}

int		mouse_hook_move(int x, int y, t_scene *scene)
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
		uv = get_uv(0, x, y);
		ray.origin = scene->camera->origin;
		ray.direction = calculate_ray_direction(scene, \
					(t_vec3f){uv.x, uv.y, scene->camera->direction.z});
		hit_info = trace_ray(scene, ray);
		printf("%f %f %f %X\n", hit_info.position.x, hit_info.position.y, hit_info.position.z, get_pixel(&scene->mlx->img, x, y));
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
