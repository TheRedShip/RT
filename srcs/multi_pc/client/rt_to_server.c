/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_to_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:12:26 by tomoron           #+#    #+#             */
/*   Updated: 2024/04/30 18:22:04 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int		open_client_socket(char *ip, uint16_t port)
{
	int sock_fd;
	struct sockaddr_in serv_addr;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0)
	{
		perror("socket");
		return(-1);
	}
	ft_bzero(&serv_addr, sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = port >> 8 | port << 8;
	if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("connect");
		close(sock_fd);
		return(-1);
	}
	return(sock_fd);
}

int		send_map(t_scene *scene, t_vec3f **map)
{
	int dest_fd;
	int i;

	dest_fd = open_client_socket(scene->server.ip, scene->server.port);
	if(dest_fd < 0)
		return(0);
	i = 0;
	while(i < HEIGHT)
	{
		if(write(dest_fd, map[i], WIDTH * sizeof(t_vec3f)) < 0)
		{
			close(dest_fd);
			return(0);
		}
		i++;
	}
	close(dest_fd);
	return(1);
}

void	rt_to_server(t_scene *scene, char *ip, char *port_str)
{
	int port;

	port = ft_atoi(port_str);
	if(port < 0 || port > 65535)
	{
		fprintf(stderr, "invalid port, must be between 0 and 65535\n");
		return ;
	}
	scene->server.ip = ip;
	scene->server.port = port;
	scene->mlx->is_acc = 0;
	while(!scene->server.error)
		rt_render_scene((void *)scene);
}
