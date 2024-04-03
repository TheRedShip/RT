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

t_vec3f	normalize(t_vec3f v)
{
	return (vec3f_div_f(v, sqrt(v.x * v.x + v.y * v.y + v.z * v.z)));
}

t_vec3f	clamp(t_vec3f vec, float min, float max)
{
	return ((t_vec3f){fminf(fmaxf(vec.x, min), max), \
						fminf(fmaxf(vec.y, min), max), \
						fminf(fmaxf(vec.z, min), max)});
}

t_vec3f	reflect(t_vec3f vec, t_vec3f normal)
{
	return (vec3f_sub_v(vec, vec3f_mul_f(normal, 2 * vec3f_dot_v(vec, normal))));
}

t_vec3f	cross(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.y * b.z - a.z * b.y, \
						a.z * b.x - a.x * b.z, \
						a.x * b.y - a.y * b.x});
}