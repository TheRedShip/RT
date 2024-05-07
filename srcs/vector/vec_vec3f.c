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

t_vec3f	v_add_v(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3f	v_sub_v(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3f	v_mul_v(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vec3f	v_div_v(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x / b.x, a.y / b.y, a.z / b.z});
}
