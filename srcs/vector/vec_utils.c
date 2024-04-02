/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:30:51 by marvin            #+#    #+#             */
/*   Updated: 2024/04/01 00:30:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec3f_dot_v(t_vec3f a, t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vec3f_len(t_vec3f vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3f	normalize(t_vec3f vec)
{
	float	len;

	len = vec3f_len(vec);
	return (vec3f_div_f(vec, len));
}

t_vec3f	clamp(t_vec3f vec, float min, float max)
{
	vec.x = fminf(fmaxf(vec.x, min), max);
	vec.y = fminf(fmaxf(vec.y, min), max);
	vec.z = fminf(fmaxf(vec.z, min), max);
	return (vec);
}

t_vec3f	reflect(t_vec3f vec, t_vec3f normal)
{
	return (vec3f_sub_v(vec, vec3f_mul_f(normal, 2 * vec3f_dot_v(vec, normal))));
}