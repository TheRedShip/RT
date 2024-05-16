/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:10:50 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/16 17:18:26 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	get_buffer_str_len(t_buffer *buffer)
{
	unsigned int	res;

	res = 0;
	while (buffer)
	{
		res += buffer->len;
		buffer = buffer->prev;
	}
	return (res);
}

void	copy_buffer(char *res, t_buffer *buffer)
{
	int	i;

	while (buffer->prev)
		buffer = buffer->prev;
	while (buffer)
	{
		i = 0;
		while (i < buffer->len)
		{
			*res = buffer->str[i];
			res++;
			i++;
		}
		buffer = buffer->next;
	}
}

void	free_buffer(t_buffer *buffer)
{
	t_buffer	*tmp;

	if (!buffer)
		return ;
	while (buffer->next)
		buffer = buffer->next;
	while (buffer)
	{
		tmp = buffer->prev;
		free(buffer);
		buffer = tmp;
	}
}

int	add_buffer(t_buffer **buffer)
{
	t_buffer	*new;

	if (*buffer && (*buffer)->nb == MAX_BUFFER)
		return (0);
	new = malloc(sizeof(t_buffer));
	if (!new)
		return (0);
	new->next = 0;
	new->len = 0;
	new->prev = *buffer;
	if (*buffer)
		new->nb = (*buffer)->nb + 1;
	else
		new->nb = 1;
	if (*buffer)
		(*buffer)->next = new;
	*buffer = new;
	return (1);
}

char	*buffer_to_str(t_buffer *buffer, int srv_size, t_scene *scene)
{
	char	*res;
	long	len;

	len = get_buffer_str_len(buffer);
	if (scene)
	{
		pthread_mutex_lock(&scene->server.mutex);
		scene->server.acc_block_received += (len / 1000);
		pthread_mutex_unlock(&scene->server.mutex);
	}
	if ((srv_size && len != ((long)(WIDTH * HEIGHT * sizeof(t_vec3f)) + 1))
		|| (!srv_size && len < (long)(sizeof(t_vec3f) * 2) + 1))
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
