/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:10:11 by tomoron           #+#    #+#             */
/*   Updated: 2024/04/30 13:53:28 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	add_thread(t_srv_threads **thrds)
{
	t_srv_threads	*new;

	new = malloc(sizeof(t_threads));
	if (!new)
		return (0);
	new->prev = *thrds;
	*thrds = new;
	return (1);
}

void	wait_threads(t_srv_threads *thrds)
{
	t_srv_threads	*tmp;

	while (thrds->prev)
	{
		tmp = thrds->prev;
		pthread_join(thrds->id, 0);
		free(thrds);
		thrds = tmp;
	}
}
