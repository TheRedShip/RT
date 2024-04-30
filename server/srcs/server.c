/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:24:35 by tomoron           #+#    #+#             */
/*   Updated: 2024/04/30 02:24:48 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/server.h"

int	g_stop = 0;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("stop signal received, waiting for all the connections to stop..\
.\n");
		g_stop = 1;
	}
}

int	setup_socket(int port)
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

int	main(void)
{
	int	socket;

	signal(SIGINT, signal_handler);
	socket = setup_socket(1880);
	if (socket < 0)
		return (1);
	wait_clients(socket);
	close(socket);
}
