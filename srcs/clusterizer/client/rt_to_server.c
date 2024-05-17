/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_to_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:12:26 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/17 15:51:00 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	wait_for_server(t_scene *scene)
{
	int	fd;

	fd = -1;
	while (fd < 0)
	{
		sleep(1);
		fd = open_client_socket(scene->server.ip, scene->server.port);
	}
	check_scene_data(fd, scene, 1);
	close(fd);
}

void	render_server(t_scene *scene)
{
	if (!send_img(scene, scene->mlx->acc_img))
	{
		printf("\nwaiting for server...\n");
		wait_for_server(scene);
		printf("server back\n");
	}
}

void	check_send_time(t_scene *scene)
{
	scene->server.send_time = get_time() - scene->server.send_time;
	if (scene->server.send_time >= MAX_SEND_TIME)
	{
		if(scene->server.nb_acc != 255)
		{
			scene->server.nb_acc++;
			printf("\nnetwork bottleneck detected, increasing number of images to %\
d\n", scene->server.nb_acc);
		}
		else
			printf("\nnetwork bottleneck detected, can't increase, too many images\n");
	}
}

int	send_img(t_scene *scene, t_vec3f **img)
{
	int			dest_fd;
	int			i;

	if (scene->mlx->frame_index < scene->server.nb_acc)
		return (1);
	scene->server.send_time = get_time();
	dest_fd = open_client_socket(scene->server.ip, scene->server.port);
	if (dest_fd < 0)
		return (0);
	if (!check_scene_data(dest_fd, scene, 0))
		return (close(dest_fd) + 1);
	write(dest_fd, &scene->server.nb_acc, 1);
	write(dest_fd, &scene->camera->origin, sizeof(t_vec3f) * 2);
	i = -1;
	while (++i < HEIGHT)
	{
		if (write(dest_fd, img[i], WIDTH * sizeof(t_vec3f)) < 0)
		{
			close(dest_fd);
			return (0);
		}
	}
	close(dest_fd);
	scene->mlx->frame_index = 0;
	check_send_time(scene);
	return (1);
}

void	rt_to_server(t_scene *scene, char *ip, char *port_str)
{
	int	port;

	signal(SIGPIPE, SIG_IGN);
	port = ft_atoi(port_str);
	if (port < 0 || port > 65535)
	{
		fprintf(stderr, "invalid port, must be between 0 and 65535\n");
		return ;
	}
	scene->server.ip = ip;
	scene->server.port = port;
	scene->server.nb_acc = 1;
	while (1)
		rt_render_scene((void *)scene);
}
