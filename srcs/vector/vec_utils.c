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

__always_inline
float	v_dot(t_vec3f a, t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

__always_inline
t_vec3f	normalize(t_vec3f v)
{
	return (v_div_f(v, sqrt(v.x * v.x + v.y * v.y + v.z * v.z)));
}

__always_inline
t_vec3f	clamp_max(t_vec3f vec, float max)
{
	return ((t_vec3f){fminf(vec.x, max), \
						fminf(vec.y, max), \
						fminf(vec.z, max)});
}

__always_inline
t_vec3f	reflect(t_vec3f vec, t_vec3f normal)
{
	return (v_sub_v(vec, v_mul_f(normal, 2 * v_dot(vec, normal))));
}

__always_inline
t_vec3f	refract(t_vec3f uv, t_vec3f n, float etai_over_etat)
{
	float	cos_theta;
	t_vec3f	r_out_perp;
	t_vec3f	r_out_parallel;

	cos_theta = fminf(v_dot(v_mul_f(uv, -1), n), 1.0);
	r_out_perp = v_mul_f(v_add_v(uv, v_mul_f(n, cos_theta)), etai_over_etat);
	r_out_parallel = v_mul_f(n, \
			-sqrt(fabs(1.0 - v_dot(r_out_perp, r_out_perp))));
	return (v_add_v(r_out_perp, r_out_parallel));
}
