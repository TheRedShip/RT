/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_to_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:12:26 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/12 19:45:37 by tomoron          ###   ########.fr       */
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

char	*get_scene_name(int fd)
{
	int			i;
	int			read_len;
	int			msg_len;
	t_buffer	*buffer;

	buffer = 0;
	msg_len = 0;
	read_len = 1;
	while (read_len)
	{
		if (!add_buffer(&buffer))
		{
			fprintf(stderr, "too much data from fd %d\n", fd);
			free_buffer(buffer);
			return (0);
		}
		read_len = read(fd, buffer->str, SOCKET_BUFFER_SIZE);
		msg_len += read_len;
		buffer->len = read_len;
		i = -1;
		while (++i < read_len && msg_len > (int) sizeof(t_vec3f) * 2)
			if (!buffer->str[i])
				read_len = 0;
	}
	return (buffer_to_str(buffer, 0, 0));
}

void	change_scene(t_scene *scene, char *scene_name)
{
	rt_free_scene(scene, 0);
	init_scene(scene_name, scene);
	create_window(scene, 1);
	scene->objects = 0;
	scene->server.nb_acc = 1;
	rt_parse(scene_name, scene);
	link_portals(scene);
	printf("\nParsing successful\n");
	if (scene->kdtree->is_bvh)
		create_bvh(scene);
	printf("Parsing complete\n");
}

int	check_scene_data(int dest_fd, t_scene *scene, int force)
{
	char	*srv_data;
	char	*ptr;

	srv_data = get_scene_name(dest_fd);
	if (!srv_data)
		return (0);
	ptr = srv_data;
	srv_data += sizeof(t_vec3f) * 2;
	if (ft_strcmp(srv_data, scene->name) || force)
	{
		printf("\nchanging to map %s\n", srv_data);
		change_scene(scene, srv_data);
		return (0);
	}
	if (ft_memcmp(&scene->camera->origin, ptr, sizeof(t_vec3f) * 2))
	{
		ft_memcpy(&scene->camera->origin, ptr, sizeof(t_vec3f) * 2);
		scene->server.nb_acc = 1;
		return(0);
	}
	free(ptr);
	return (1);
}

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

int	send_img(t_scene *scene, t_vec3f **img)
{
	int			dest_fd;
	int			i;

	if(scene->mlx->frame_index < scene->server.nb_acc)
		return(1);
	scene->server.send_time = get_time();
	dest_fd = open_client_socket(scene->server.ip, scene->server.port);
	if (dest_fd < 0)
		return (0);
	if(!check_scene_data(dest_fd, scene, 0))
		return(close(dest_fd) + 1);
	write(dest_fd, &scene->server.nb_acc, 1);
	i = 0;
	while (i < HEIGHT)
	{
		if (write(dest_fd, img[i], WIDTH * sizeof(t_vec3f)) < 0)
		{
			close(dest_fd);
			return (0);
		}
		i++;
	}
	close(dest_fd);
	scene->mlx->frame_index = 0;
	scene->server.send_time = get_time() - scene->server.send_time;
	if(scene->server.send_time >= MAX_SEND_TIME)
	{
		scene->server.nb_acc++;
		printf("\nnetwork bottleneck detected, increasing number of images to %d\n", scene->server.nb_acc);
	}
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
