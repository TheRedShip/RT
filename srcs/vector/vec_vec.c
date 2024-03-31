/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:28:05 by marvin            #+#    #+#             */
/*   Updated: 2024/03/31 00:28:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec2f	vec2f_add_v(t_vec2f a, t_vec2f b)
{
	t_vec2f	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vec2f	vec2f_sub_v(t_vec2f a, t_vec2f b)
{
	t_vec2f	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

t_vec2f	vec2f_mul_v(t_vec2f a, t_vec2f b)
{
	t_vec2f	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	return (result);
}

t_vec2f	vec2f_div_v(t_vec2f a, t_vec2f b)
{
	t_vec2f	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	return (result);
}

float	vec3f_dot_v(t_vec3f a, t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}