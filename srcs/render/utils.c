/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:58:22 by marvin            #+#    #+#             */
/*   Updated: 2024/04/01 00:58:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_hex(t_vec3f rgb)
{
	return(0xFF << 24 | (int)rgb.x << 16 |  (int)rgb.y << 8 | (int)rgb.z);
}

int	ft_random(int i)
{
	static int seeds[THREADS] = {0};

	if (seeds[i] == 0)
		seeds[i] = rand();
	 seeds[i] = seeds[i] * 1103515245 + 12345;
	return ((unsigned int)(seeds[i]) % 2147483647);
}