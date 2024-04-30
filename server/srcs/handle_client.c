/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:12:14 by tomoron           #+#    #+#             */
/*   Updated: 2024/04/30 02:21:42 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*get_client_data(int fd)
{
	t_buffer	*buffer;
	int			read_len;
	char		*res;

	buffer = 0;
	read_len = BUFFER_SIZE - 1;
	while (read_len)
	{
		if (!add_buffer(&buffer))
		{
			free_buffer(buffer);
			return (0);
		}
		read_len = read(fd, buffer->str, BUFFER_SIZE - 1);
		buffer->len = read_len;
		buffer->str[read_len] = 0;
	}
	res = malloc(get_buffer_str_len(buffer) + 1);
	if (res)
		copy_buffer(res, buffer);
	free_buffer(buffer);
	return (res);
}

void	*handle_client(void *data)
{
	long int	client_fd;
	char		*client_data;

	client_fd = (long int)data;
	printf("connection :%ld\n", client_fd);
	client_data = get_client_data(client_fd);
	close(client_fd);
	if (client_data)
		printf("data : %s\n", client_data);
	return (0);
}

void	wait_clients(int socket)
{
	struct sockaddr_in	client;
	socklen_t			client_addr_len;
	long int			client_fd;
	t_threads			*threads;

	client_addr_len = sizeof(struct sockaddr_in);
	threads = 0;
	while (!g_stop)
	{
		client_fd = accept(socket, (struct sockaddr *)&client, \
		&client_addr_len);
		if (client_fd < 0)
			perror("accept");
		else
		{
			if (!add_thread(&threads) || pthread_create(&threads->id, NULL, \
			handle_client, (void *)client_fd))
			{
				close(client_fd);
				g_stop = 1;
				continue ;
			}
		}
	}
	wait_threads(threads);
}
