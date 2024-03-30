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

t_vec2f    vec2f_add_f(t_vec2f a, float b)
{
	t_vec2f result;

	result.x = a.x + b;
	result.y = a.y + b;
	return (result);
}

t_vec2f    vec2f_mul_f(t_vec2f a, float b)
{
	t_vec2f result;

	result.x = a.x * b;
	result.y = a.y * b;
	return (result);
}

t_vec2f    vec2f_div_f(t_vec2f a, float b)
{
	t_vec2f result;

	result.x = a.x / b;
	result.y = a.y / b;
	return (result);
}