/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:01:19 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/12 21:01:25 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	open_client_socket(char *ip, uint16_t port)
{
	int					sock_fd;
	struct sockaddr_in	serv_addr;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		return (-1);
	}
	ft_bzero(&serv_addr, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = port >> 8 | port << 8;
	if (connect(sock_fd, (struct sockaddr *)&serv_addr, \
		sizeof(struct sockaddr_in)) < 0)
	{
		close(sock_fd);
		return (-1);
	}
	return (sock_fd);
}
