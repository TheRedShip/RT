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

void moveCamera(t_scene *scene, t_vec3f movement)
{
	t_vec3f		rotatedMovement;

	multiplyMatrixVector(scene->camera->rotationMatrixX, movement, &rotatedMovement);
	multiplyMatrixVector(scene->camera->rotationMatrixY, rotatedMovement, &rotatedMovement);
    scene->camera->origin = vec3f_add_v(scene->camera->origin, rotatedMovement);
}

int		key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_FORW)
		moveCamera(scene, (t_vec3f){0, 0, -0.15f});
	else if (keycode == KEY_BACK)
		moveCamera(scene, (t_vec3f){0, 0, 0.15f});
	else if (keycode == KEY_LEFT)
		moveCamera(scene, (t_vec3f){-0.15f, 0, 0});
	else if (keycode == KEY_RIGHT)
		moveCamera(scene, (t_vec3f){0.15f, 0, 0});
	else if (keycode == KEY_UPE)
		moveCamera(scene, (t_vec3f){0, 0.15f, 0});
	else if (keycode == KEY_DOWNA)
		moveCamera(scene, (t_vec3f){0, -0.15f, 0});
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
	t_vec3f mouse_delta;
	
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

int		mouse_hook_press(int button, int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	if (button == 3)
	{
		scene->mlx->frame_index = 1;
		scene->mouse.is_pressed = 1;
	}
	else if (button == 1)
	{
		t_vec2f uv = get_uv(x, y);
		t_ray	ray;
		ray.origin = scene->camera->origin;
		ray.direction = calculate_ray_direction(scene, (t_vec3f){uv.x, uv.y, scene->camera->direction.z});

		t_hitInfo hit_info = trace_ray(scene, ray);
		printf("%f %f %f %X\n", hit_info.position.x, hit_info.position.y, hit_info.position.z, get_pixel(&scene->mlx->img, x, y));
	}
	return (0);
}

int		mouse_hook_release(int button, int x, int y, t_scene *scene)
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
