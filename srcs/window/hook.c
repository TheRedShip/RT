/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:12:28 by marvin            #+#    #+#             */
/*   Updated: 2024/03/30 23:12:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void moveCamera(t_camera *camera, t_vec3f movement)
{
	t_vec3f	rotatedMovement;

	multiplyMatrixVector(camera->rotationMatrixX, movement, &rotatedMovement);
	multiplyMatrixVector(camera->rotationMatrixY, rotatedMovement, &rotatedMovement);
    camera->origin = vec3f_add_v(camera->origin, rotatedMovement);
}

int		key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_FORW)
		moveCamera(scene->camera, (t_vec3f){0, 0, -0.15f});
	else if (keycode == KEY_BACK)
		moveCamera(scene->camera, (t_vec3f){0, 0, 0.15f});
	else if (keycode == KEY_LEFT)
		moveCamera(scene->camera, (t_vec3f){-0.15f, 0, 0});
	else if (keycode == KEY_RIGHT)
		moveCamera(scene->camera, (t_vec3f){0.15f, 0, 0});
	else if (keycode == KEY_UPE)
		moveCamera(scene->camera, (t_vec3f){0, 0.15f, 0});
	else if (keycode == KEY_DOWNA)
		moveCamera(scene->camera, (t_vec3f){0, -0.15f, 0});
	else if (keycode == KEY_ESCH)
		rt_free_scene(scene);
	else if (keycode == KEY_ENTER)
		scene->mlx->is_acc = !scene->mlx->is_acc;
	if (keycode < 65000)
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
		printf("color: %X\n", *(unsigned int *)(scene->mlx->img.addr + (y * scene->mlx->img.line_length + x * (scene->mlx->img.bits_per_pixel / 8))));
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