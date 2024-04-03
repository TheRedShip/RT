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

t_vec3f    vec3f_add_f(t_vec3f a, float b)
{
	return ((t_vec3f){a.x + b, a.y + b, a.z + b});
}

t_vec3f    vec3f_mul_f(t_vec3f a, float b)
{
	return ((t_vec3f){a.x * b, a.y * b, a.z * b});
}

t_vec3f    vec3f_div_f(t_vec3f a, float b)
{
	return ((t_vec3f){a.x / b, a.y / b, a.z / b});
}