/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:56:51 by marvin            #+#    #+#             */
/*   Updated: 2024/04/02 20:56:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f		**init_acc_img(t_scene *scene)
{
	t_vec3f	**acc_img;
	int		i;

	acc_img = ft_calloc(HEIGHT + 1, sizeof(t_vec3f *));
	if (!acc_img)
		rt_free_scene(scene);
	i = 0;
	while (i < HEIGHT)
	{
		acc_img[i] = ft_calloc(WIDTH + 1, sizeof(t_vec3f));
		if (!acc_img[i])
			rt_free_scene(scene);
		i++;
	}
	return (acc_img);
}