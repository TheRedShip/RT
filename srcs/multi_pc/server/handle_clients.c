/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_clients.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:12:14 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/06 19:36:55 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*buffer_to_str(t_buffer *buffer, int expect_size)
{
	char	*res;
	int		len;

	len = get_buffer_str_len(buffer);
	if (expect_size && len != (unsigned)(WIDTH * HEIGHT * sizeof(t_vec3f)))
	{
		free_buffer(buffer);
		return (0);
	}
	res = malloc(len);
	if (!res)
		fprintf(stderr, "malloc failed\n");
	if (res)
		copy_buffer(res, buffer);
	free_buffer(buffer);
	return (res);
}

char	*get_client_data(int fd)
{
	t_buffer	*buffer;
	int			read_len;

	buffer = 0;
	read_len = SOCKET_BUFFER_SIZE - 1;
	while (read_len)
	{
		if (!add_buffer(&buffer))
		{
			fprintf(stderr, "too much data from fd %d\n", fd);
			free_buffer(buffer);
			return (0);
		}
		read_len = read(fd, buffer->str, SOCKET_BUFFER_SIZE);
		buffer->len = read_len;
	}
	return (buffer_to_str(buffer, 1));
}

void	add_to_acc_img(t_vec3f *data, t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (scene->mlx->is_acc)
				scene->mlx->acc_img[i][j] = \
				vec3f_add_v(scene->mlx->acc_img[i][j], data[i * WIDTH + j]);
			else
				scene->mlx->acc_img[i][j] = data[i * WIDTH + j];
			scene->mlx->final_img[i][j] = \
				vec3f_div_f(scene->mlx->acc_img[i][j], scene->mlx->frame_index);
			j++;
		}
		i++;
	}
}

void	*handle_client(void *data)
{
	int				client_fd;
	t_scene			*scene;
	char			*client_data;
	t_thread_data	*patate;

	patate = data;
	client_fd = patate->fd;
	scene = patate->scene;
	write(client_fd, scene->name, ft_strlen(scene->name) + 1);
	client_data = get_client_data(client_fd);
	close(client_fd);
	pthread_mutex_lock(&scene->server.mutex);
	if (!scene->server.stop && client_data)
	{
		add_to_acc_img((t_vec3f *)client_data, scene); 
		if (scene->mlx->is_acc)
			scene->mlx->frame_index++;
		printf("accumulation : %lums, %d         \r", get_time() - \
				scene->server.last_img_time, scene->mlx->frame_index);
		fflush(stdout);
		scene->server.last_img_time = get_time();
	}
	free(client_data);
	pthread_mutex_unlock(&scene->server.mutex);
	free(data);
	return (0);
}

void	wait_clients(t_scene *scene, int socket)
{
	struct sockaddr_in	client;
	socklen_t			client_addr_len;
	long int			client_fd;
	t_srv_threads		*threads;
	t_thread_data		*thread_data;

	client_addr_len = sizeof(struct sockaddr_in);
	threads = 0;
	while (!get_stopped(scene))
	{
		client_fd = accept(socket, (struct sockaddr *)&client, \
		&client_addr_len);
		if (client_fd < 0)
			perror("accept");
		else
		{
			thread_data = malloc(sizeof(t_thread_data));
			if (!thread_data)
			{
				close(client_fd);
				continue ;
			}
			thread_data->fd = client_fd;
			thread_data->scene = scene;
			if (!add_thread(&threads) || pthread_create(&threads->id, NULL, \
			handle_client, (void *)thread_data))
			{
				wait_threads(threads);
				close(client_fd);
				continue ;
			}
		}
	}
	wait_threads(threads);
}
