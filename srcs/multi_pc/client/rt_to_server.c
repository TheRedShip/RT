/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_to_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:12:26 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/02 18:06:00 by tomoron          ###   ########.fr       */
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
		return(-1);
	}
	ft_bzero(&serv_addr, sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = port >> 8 | port << 8;
	if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0)
	{
		close(sock_fd);
		return(-1);
	}
	return(sock_fd);
}

char	*get_scene_name(int fd)
{
	int i;
	int read_len;
	t_buffer *buffer;

	buffer = 0;	
	read_len = 1;
	while(read_len)
	{	
		if (!add_buffer(&buffer))
		{
			fprintf(stderr, "too much data from fd %d\n", fd);
			free_buffer(buffer);
			return (0);
		}
		read_len = read(fd, buffer->str, SOCKET_BUFFER_SIZE);
		buffer->len = read_len;
		i = 0;
		while(i < read_len)
		{
			if(!buffer->str[i])
				read_len = 0;
			i++;
		}
	}
	return (buffer_to_str(buffer, 0));
}

void			rt_free_scene_replace(t_scene *scene)
{
	t_objects	*tmp;

	free(scene->ambient_light);
	free(scene->camera);
	free(scene->lights);
	free(scene->bloom);
	free(scene->name);
	while (scene->objects)
	{
		tmp = scene->objects;
		scene->objects = scene->objects->next;
		free(tmp->sphere);
		free(tmp->plane);
		free(tmp->cylinder);
		free(tmp->ellipse);
		free(tmp->quad);	
		free(tmp->portal);
		free(tmp);
	}
}

int	change_scene(t_scene *scene, char *scene_name)
{
	rt_free_scene_replace(scene);
	init_scene(scene_name, 1, scene);
	scene->objects = 0;
	scene->mlx->is_acc = 0;
	rt_parse(scene_name, &scene);
	link_portals(scene);
	free(scene_name);
	printf("\nParsing successful\n");
	return(1);
}

void	wait_for_server(t_scene *scene)
{
	int fd;

	fd = -1;
	while (fd < 0)
	{
		sleep(1);
		fd = open_client_socket(scene->server.ip, scene->server.port);
	}
	close(fd);
}

int		send_map(t_scene *scene, t_vec3f **map)
{
	int		dest_fd;
	int		i;
	char	*scene_name;

	dest_fd = open_client_socket(scene->server.ip, scene->server.port);
	if(dest_fd < 0)
		return(0);
	scene_name = get_scene_name(dest_fd);
	if(ft_strcmp(scene_name, scene->name))
	{
		printf("\nchanging to map %s\n", scene_name);
		close(dest_fd);
		return(change_scene(scene, scene_name));
	}
	free(scene_name);
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
	while(!scene->server.stop)
		rt_render_scene((void *)scene);
	rt_free_scene(scene);
}
