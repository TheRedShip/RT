/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:01:18 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/12 22:15:56 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_stopped(t_scene *scene)
{
	int	res;

	pthread_mutex_lock(&scene->server.mutex);
	res = scene->server.stop;
	pthread_mutex_unlock(&scene->server.mutex);
	return (res);
}

void	set_stopped(t_scene *scene)
{
	pthread_mutex_lock(&scene->server.mutex);
	scene->server.stop = 1;
	pthread_mutex_unlock(&scene->server.mutex);
}
