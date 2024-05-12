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
	rgb.x = sqrt(rgb.x);
	rgb.y = sqrt(rgb.y);
	rgb.z = sqrt(rgb.z);
	rgb = v_mul_f(rgb, 255.0f);
	return (0xFF << 24 | (int)rgb.x << 16 | (int)rgb.y << 8 | (int)rgb.z);
}

t_vec3f	hex_to_rgb(int hex)
{
	t_vec3f	rgb;

	rgb.x = (hex >> 16) & 0xFF;
	rgb.y = (hex >> 8) & 0xFF;
	rgb.z = hex & 0xFF;
	rgb = v_div_f(rgb, 255.0f);
	return (rgb);
}

t_vec3f	lerp(t_vec3f a, t_vec3f b, float t)
{
	return (v_add_v(v_mul_f(a, t), v_mul_f(b, 1.0f - t)));
}

float	ft_random(int i, int min, int max)
{
	static int	seeds[THREADS] = {0};

	if (seeds[i] == 0)
		seeds[i] = rand();
	seeds[i] = seeds[i] * 1103515245 + 12345;
	return (min + (float)((unsigned int)(seeds[i]) % 2147483647) / \
		(2147483647.) * (max - min));
}

t_vec2f	get_uv(t_threads *thread, float x, float y)
{
	static float	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	t_vec2f			uv;

	if (thread && thread->scene->mlx->antialiasing)
	{
		x += (float)(ft_random(thread->id, -1, 1));
		y += (float)(ft_random(thread->id, -1, 1));
	}
	uv = (t_vec2f){(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
	uv.x = uv.x * 2.0f - 1.0f;
	uv.y = uv.y * 2.0f - 1.0f;
	uv.y = -uv.y;
	uv.x *= aspect_ratio;
	return (uv);
}
