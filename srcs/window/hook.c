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

int		key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_FORW)
		scene->camera->origin = vec3f_add_v(scene->camera->origin, (t_vec3f){0, 0, -0.1f});
	else if (keycode == KEY_BACK)
		scene->camera->origin = vec3f_add_v(scene->camera->origin, (t_vec3f){0, 0, 0.1f});
	else if (keycode == KEY_LEFT)
		scene->camera->origin = vec3f_add_v(scene->camera->origin, (t_vec3f){-0.1f, 0, 0});
	else if (keycode == KEY_RIGHT)
		scene->camera->origin = vec3f_add_v(scene->camera->origin, (t_vec3f){0.1f, 0, 0});
	else if (keycode == KEY_SPACE)
		scene->camera->origin = vec3f_add_v(scene->camera->origin, (t_vec3f){0, 0.1f, 0});
	else if (keycode == KEY_SHIFT)
		scene->camera->origin = vec3f_add_v(scene->camera->origin, (t_vec3f){0, -0.1f, 0});
	else if (keycode == KEY_ESCH)
		rt_free_scene(scene);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	(void)scene;
	if (button == 1)
		printf("Left click\n");
	else if (button == 2)
		printf("Right click\n");
	return (0);
}