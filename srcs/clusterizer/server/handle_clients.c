/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_clients.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:12:14 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/16 17:17:31 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	send_data_to_client(int client_fd, t_scene *scene)
{
	int	ret;

	ret = write(client_fd, &scene->camera->origin, sizeof(t_vec3f) * 2);
	if (ret < 0)
		return (0);
	ret = write(client_fd, scene->name, ft_strlen(scene->name) + 1);
	return (ret > 0);
}

char	*get_client_data(t_scene *scene, int fd)
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
	return (buffer_to_str(buffer, 1, scene));
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
			if (scene->mlx->is_acc && scene->mlx->frame_index > 1)
				scene->mlx->acc_img[i][j] = \
				v_add_v(scene->mlx->acc_img[i][j], data[i * WIDTH + j]);
			else
				scene->mlx->acc_img[i][j] = data[i * WIDTH + j];
			scene->mlx->final_img[i][j] = \
				v_div_f(scene->mlx->acc_img[i][j], scene->mlx->frame_index);
			j++;
		}
		i++;
	}
}

void	handle_client_data(char *client_data, t_scene *scene)
{
	add_to_acc_img((t_vec3f *)(client_data + 1), scene);
	if (scene->mlx->is_acc)
		scene->mlx->frame_index += *(uint8_t *)client_data;
	if (scene->mlx->frame_index <= 3)
	{
		scene->server.acc_start_time = get_time();
		scene->server.acc_block_received = 0;
	}
	printf("time : %lums, frames: %d, speed: %.2f MB/s                    \r", \
		get_avg_time(scene), scene->mlx->frame_index, get_avg_speed(scene));
	fflush(stdout);
}

void	*handle_client(void *data_ptr)
{
	int				client_fd;
	t_scene			*scene;
	char			*client_data;
	t_thread_data	*data;

	data = data_ptr;
	client_fd = data->fd;
	scene = data->scene;
	pthread_mutex_lock(&scene->server.mutex);
	if (!send_data_to_client(client_fd, scene))
	{
		close(client_fd);
		free(data);
		pthread_mutex_unlock(&scene->server.mutex);
		return (0);
	}
	client_data = get_client_data(scene, client_fd);
	close(client_fd);
	if (!scene->server.stop && client_data)
		handle_client_data(client_data, scene);
	free(client_data);
	pthread_mutex_unlock(&scene->server.mutex);
	free(data);
	return (0);
}
