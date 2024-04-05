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

typedef struct	s_vec3f
{
	float	x;
	float	y;
	float	z;
}				t_vec3f;

typedef struct	s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

t_vec3f		vec3f_add_f(t_vec3f a, float b);
t_vec3f		vec3f_mul_f(t_vec3f a, float b);
t_vec3f		vec3f_div_f(t_vec3f a, float b);

t_vec3f		vec3f_add_v(t_vec3f a, t_vec3f b);
t_vec3f		vec3f_sub_v(t_vec3f a, t_vec3f b);
t_vec3f		vec3f_mul_v(t_vec3f a, t_vec3f b);
t_vec3f   	vec3f_div_v(t_vec3f a, t_vec3f b);
float		vec3f_dot_v(t_vec3f a, t_vec3f b);

t_vec3f		normalize(t_vec3f vec);
t_vec3f		clamp(t_vec3f vec, float min, float max);
t_vec3f		reflect(t_vec3f vec, t_vec3f normal);
t_vec3f		cross(t_vec3f a, t_vec3f b);

float		ft_random(int thread_id, int min, int max);
t_vec3f		lerp(t_vec3f a, t_vec3f b, float t);

void		apply_rotationMatrixX(float angle, float (*matrix)[3]);
void		apply_rotationMatrixY(float angle, float (*matrix)[3]);
void		multiplyMatrixVector(float (*matrix)[3], t_vec3f vector, t_vec3f *result);

#endif