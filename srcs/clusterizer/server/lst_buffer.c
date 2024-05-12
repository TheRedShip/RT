/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:10:50 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/06 19:40:48 by ycontre          ###   ########.fr       */
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
