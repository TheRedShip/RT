/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:24:35 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/01 18:49:57 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	setup_socket(uint16_t port)
{
	int					server_fd;
	struct sockaddr_in	s_addr;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		perror("socket");
	if (server_fd < 0)
		return (-1);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = INADDR_ANY;
	s_addr.sin_port = port >> 8 | port << 8;
	if (bind(server_fd, (struct sockaddr *)&s_addr, \
	sizeof(struct sockaddr_in)) < 0)
	{
		close(server_fd);
		perror("bind");
		return (-1);
	}
	if (listen(server_fd, 50) < 0)
	{
		close(server_fd);
		perror("listen");
		return (-1);
	}
	return (server_fd);
}

int	start_server(t_scene *scene, char *port_str)
{
	int	socket;
	uint16_t port;
	pthread_t	mlx_thread;

	port = ft_atoi(port_str);
	if(pthread_mutex_init(&scene->server.mutex, 0))
		return(1);
	mlx_thread = init_server_hooks(scene);
	if(port >= 65535 || port <= 0)
	{
		fprintf(stderr, "invalid port, must be between 0 and 65535\n");
		return(1);
	}
	socket = setup_socket(port);
	if (socket < 0)
		return (1);
	scene->server.last_img_time = get_time();
	wait_clients(scene, socket);
	close(socket);
	pthread_join(mlx_thread, 0);
	rt_free_scene(scene);
	return(0);
}
