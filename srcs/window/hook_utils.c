/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:49:11 by ycontre           #+#    #+#             */
/*   Updated: 2024/05/10 00:47:36 by marvin           ###   ########.fr       */
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

int	key_move_hook(int keycode, t_scene *scene)
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
	else
		return (0);
	return (1);
}

void	key_settings_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ENTER)
	{
		scene->mlx->is_acc = !scene->mlx->is_acc;
		printf("miniRT : accumulating %d      \n", scene->mlx->is_acc);
	}
	else if (keycode == KEY_ALIA)
	{
		scene->mlx->frame_index = 1;
		scene->mlx->antialiasing = !scene->mlx->antialiasing;
		printf("miniRT : antialiasing %d      \n", scene->mlx->antialiasing);
	}
	else if (keycode == KEY_BLOOM)
	{
		scene->mlx->is_bloom = !scene->mlx->is_bloom;
		printf("miniRT : bloom %d             \n", scene->mlx->is_bloom);
	}
	else if (keycode == 65451 && scene->bloom->mip_num < 10)
		scene->bloom->mip_num++;
	else if (keycode == 65453 && scene->bloom->mip_num > 0)
		scene->bloom->mip_num--;
}
