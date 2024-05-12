/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:10:11 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/06 19:40:58 by ycontre          ###   ########.fr       */
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

	while (thrds)
	{
		tmp = thrds->prev;
		pthread_join(thrds->id, 0);
		free(thrds);
		thrds = tmp;
	}
}
