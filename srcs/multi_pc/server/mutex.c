/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:01:18 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/06 19:41:02 by ycontre          ###   ########.fr       */
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
