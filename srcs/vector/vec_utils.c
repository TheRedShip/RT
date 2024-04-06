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

t_vec3f	refract(t_vec3f uv, t_vec3f n, float etai_over_etat)
{
	float	cos_theta;
	t_vec3f	r_out_perp;
	t_vec3f	r_out_parallel;

	cos_theta = fminf(vec3f_dot_v(vec3f_mul_f(uv, -1), n), 1.0);
	r_out_perp = vec3f_mul_f(vec3f_add_v(uv, vec3f_mul_f(n, cos_theta)), etai_over_etat);
	r_out_parallel = vec3f_mul_f(n, -sqrt(fabs(1.0 - vec3f_dot_v(r_out_perp, r_out_perp))));
	return (vec3f_add_v(r_out_perp, r_out_parallel));
}
