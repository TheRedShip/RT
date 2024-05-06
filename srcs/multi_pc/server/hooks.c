/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:16:19 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/05 14:36:46 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_new_acc(t_scene *scene)
{
	rt_render_image(bloom(scene, scene->mlx->final_img), &scene->mlx->img);
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
}

int server_stop(void *data)
{
	t_scene *scene;

	scene = data;
	pthread_mutex_lock(&scene->server.mutex);
	scene->server.stop = 1;
	printf("stop\n");
	pthread_mutex_unlock(&scene->server.mutex);
	return(0);
}

int	server_key_hook(int key, void *data)
{
	t_scene *scene;

	scene = data;
	pthread_mutex_lock(&scene->server.mutex);
	//printf("key : %d\n", key);
	if(key == KEY_ESCH)
		scene->server.stop = 1;
	if(key == KEY_BLOOM)
		scene->mlx->is_bloom = !scene->mlx->is_bloom;	
	if(key == 65421)
	{
		scene->mlx->is_acc = !scene->mlx->is_acc;
		printf("accumulation : %d\n", scene->mlx->is_acc);
		scene->mlx->frame_index = 1 + scene->mlx->is_acc;
	}
	if(key == 65451)
		scene->bloom->mip_num++;
	if(key == 65453)
		scene->bloom->mip_num--;
	
	pthread_mutex_unlock(&scene->server.mutex);
	return(0);
}

int server_loop_hook(void *data)
{
	t_scene *scene;

	scene = data;
	if(get_stopped(scene))
	{
		mlx_loop_end(scene->mlx->mlx);
		return(0);
	}
	pthread_mutex_lock(&scene->server.mutex);
	render_new_acc(scene);
	pthread_mutex_unlock(&scene->server.mutex);
	usleep(1000 * 100);
	return(0);
}

pthread_t	init_server_hooks(t_scene *scene)
{
	pthread_t thread;
	mlx_hook(scene->mlx->win, 17, 1L << 2, server_stop, scene);
	mlx_hook(scene->mlx->win, 2, 1L << 0, server_key_hook, scene);
	mlx_loop_hook(scene->mlx->mlx, server_loop_hook, scene);
	if(pthread_create(&thread, 0, (void *(*)(void *))mlx_loop, scene->mlx->mlx))
		return(0);
	return(thread);
}
