/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:12:28 by marvin            #+#    #+#             */
/*   Updated: 2024/03/30 23:12:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		key_hook(int keycode, t_scene *scene)
{
	if (keycode == 65307)
		rt_free_scene(scene);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	(void)scene;
	if (button == 1)
		printf("Left click\n");
	else if (button == 2)
		printf("Right click\n");
	return (0);
}