/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:02:09 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/24 14:14:15 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	scene->bvh = NULL;
	scene->objects = NULL;
	scene->server.nb_acc = 1;
	rt_parse(scene_name, scene);
	link_portals(scene);
	if (scene->kdtree->is_bvh)
		create_bvh(scene);
}

int	handle_scene_data(char *ptr, t_scene *scene, int force)
{
	char	*srv_data;

	srv_data = ptr + (sizeof(t_vec3f) * 2);
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
		scene->mlx->frame_index = 0;
		reset_img(scene->mlx->acc_img);
		return (0);
	}
	free(ptr);
	return (1);
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
	if (!*srv_data)
	{
		free(srv_data);
		return (0);
	}
	return (handle_scene_data(ptr, scene, force));
}
