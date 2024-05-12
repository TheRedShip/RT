/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_clients.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:19:21 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/12 22:19:32 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	wait_for_new_client(t_scene *scene, int socket, \
	socklen_t client_addr_len, t_srv_threads **threads)
{
	t_thread_data		*thread_data;
	struct sockaddr_in	client;
	int					client_fd;

	client_fd = accept(socket, (struct sockaddr *)&client, \
	&client_addr_len);
	if (client_fd < 0)
		perror("accept");
	else
	{
		thread_data = malloc(sizeof(t_thread_data));
		if (!thread_data)
			close(client_fd);
		if (!thread_data)
			return ;
		thread_data->fd = client_fd;
		thread_data->scene = scene;
		if (!add_thread(threads) || pthread_create(&((*threads)->id), NULL, \
		handle_client, (void *)thread_data))
		{
			wait_threads(*threads);
			close(client_fd);
			return ;
		}
	}
}

void	wait_clients(t_scene *scene, int socket)
{
	socklen_t			client_addr_len;
	t_srv_threads		*threads;

	client_addr_len = sizeof(struct sockaddr_in);
	threads = 0;
	while (!get_stopped(scene))
		wait_for_new_client(scene, socket, client_addr_len, &threads);
	wait_threads(threads);
}
