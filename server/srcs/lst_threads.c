/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:10:11 by tomoron           #+#    #+#             */
/*   Updated: 2024/04/30 02:22:25 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/server.h"

int	add_thread(t_threads **thrds)
{
	t_threads	*new;

	new = malloc(sizeof(t_threads));
	if (!new)
		return (0);
	new->prev = *thrds;
	*thrds = new;
	return (1);
}

void	wait_threads(t_threads *thrds)
{
	t_thread	*tmp;

	while (thrds->prev)
	{
		tmp = thrds->prev;
		pthread_join(thrds->id, 0);
		free(thrds);
		thrds = tmp;
	}
}
