/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:38:48 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/24 13:55:17 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

long unsigned	get_avg_time(t_scene *scene)
{
	long unsigned	time;

	if (scene->mlx->frame_index <= 2)
		return (0);
	if (!scene->server.acc_start_time)
		return (0);
	time = get_time() - scene->server.acc_start_time;
	return (time / (scene->mlx->frame_index - 2));
}

float	get_avg_speed(t_scene *scene)
{
	int			s;
	float		res;
	uint64_t	nb_blocks;

	s = (get_time() - scene->server.acc_start_time) / 1000;
	if (!s)
		return (0);
	nb_blocks = scene->server.acc_block_received / 1000;
	res = (float)nb_blocks / (float)s;
	return (res);
}
