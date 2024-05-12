/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:21:00 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/12 22:21:45 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	server_stop(void *data)
{
	t_scene	*scene;

	scene = data;
	pthread_mutex_lock(&scene->server.mutex);
	scene->server.stop = 1;
	printf("stop\n");
	pthread_mutex_unlock(&scene->server.mutex);
	return (0);
}

void	reset_img(t_vec3f **img)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img[i][j] = (t_vec3f){0, 0, 0};
			j++;
		}
		i++;
	}
}

pthread_t	init_server_hooks(t_scene *scene)
{
	pthread_t	thread;

	mlx_hook(scene->mlx->win, 17, 1L << 2, server_stop, scene);
	mlx_hook(scene->mlx->win, 2, 1L << 0, server_key_hook, scene);
	mlx_hook(scene->mlx->win, 6, 1L << 6, mouse_hook_move_server, scene);
	mlx_hook(scene->mlx->win, 4, 1L << 2, mouse_hook_press_server, scene);
	mlx_hook(scene->mlx->win, 5, 1L << 3, mouse_hook_release_server, scene);
	mlx_loop_hook(scene->mlx->mlx, server_loop_hook, scene);
	if (pthread_create(&thread, 0, \
	(void *(*)(void *))mlx_loop, scene->mlx->mlx))
		return (0);
	return (thread);
}
