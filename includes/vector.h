/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:30:09 by marvin            #+#    #+#             */
/*   Updated: 2024/03/31 00:30:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

typedef struct s_vec3f
{
	float	x;
	float	y;
	float	z;
}				t_vec3f;

typedef struct s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

t_vec3f		v_add_f(t_vec3f a, float b);
t_vec3f		v_mul_f(t_vec3f a, float b);
t_vec3f		v_div_f(t_vec3f a, float b);

t_vec3f		v_add_v(t_vec3f a, t_vec3f b);
t_vec3f		v_sub_v(t_vec3f a, t_vec3f b);
t_vec3f		v_mul_v(t_vec3f a, t_vec3f b);
t_vec3f		v_div_v(t_vec3f a, t_vec3f b);

float		v_dot(t_vec3f a, t_vec3f b);
float		v_length(t_vec3f a);
t_vec3f		normalize(t_vec3f vec);
t_vec3f		clamp_max(t_vec3f vec, float max);
t_vec3f		reflect(t_vec3f vec, t_vec3f normal);
t_vec3f		refract(t_vec3f uv, t_vec3f n, float etai_over_etat);
t_vec3f		v_cross(t_vec3f a, t_vec3f b);

float		ft_random(int thread_id, int min, int max);
t_vec3f		lerp(t_vec3f a, t_vec3f b, float t);

void		apply_rotation_matrix_x(float angle, float (*matrix)[3]);
void		apply_rotation_matrix_y(float angle, float (*matrix)[3]);
void		multiply_matrix_vector(float (*matrix)[3], \
								t_vec3f vector, t_vec3f *result);

#endif