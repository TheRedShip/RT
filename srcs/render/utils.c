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

int		rgb_to_hex(t_vec3f rgb)
{
	rgb.x = sqrt(rgb.x);
	rgb.y = sqrt(rgb.y);
	rgb.z = sqrt(rgb.z);
	rgb = vec3f_mul_f(rgb, 255.0f);
	return(0xFF << 24 | (int)rgb.x << 16 |  (int)rgb.y << 8 | (int)rgb.z);
}

t_vec3f	hex_to_rgb(int hex)
{
	t_vec3f	rgb;

	rgb.x = (hex >> 16) & 0xFF;
	rgb.y = (hex >> 8) & 0xFF;
	rgb.z = hex & 0xFF;
	rgb = vec3f_div_f(rgb, 255.0f);
	return (rgb);
}

t_vec3f	lerp(t_vec3f a, t_vec3f b, float t)
{
	return (vec3f_add_v(vec3f_mul_f(a, t), vec3f_mul_f(b, 1.0f-t)));
}

float	ft_random(int i, int min, int max)
{
	static int seeds[THREADS] = {0};

	if (seeds[i] == 0)
		seeds[i] = rand();
	seeds[i] = seeds[i] * 1103515245 + 12345;
	return min + (float)((unsigned int)(seeds[i]) % 2147483647) / (float)(2147483647) * (max - min);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}