/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:29:33 by marvin            #+#    #+#             */
/*   Updated: 2024/03/31 00:29:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	v_length(t_vec3f a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3f	v_cross(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}

t_vec3f	v_add_f(t_vec3f a, float b)
{
	return ((t_vec3f){a.x + b, a.y + b, a.z + b});
}

t_vec3f	v_mul_f(t_vec3f a, float b)
{
	return ((t_vec3f){a.x * b, a.y * b, a.z * b});
}

t_vec3f	v_div_f(t_vec3f a, float b)
{
	return ((t_vec3f){a.x / b, a.y / b, a.z / b});
}
