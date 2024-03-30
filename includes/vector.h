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

typedef struct	s_vec3i
{
	int		x;
	int		y;
	int		z;
}				t_vec3i;

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

typedef struct	s_vec2i
{
	int		x;
	int		y;
}				t_vec2i;

t_vec2f    vec2f_add_f(t_vec2f a, float b);
t_vec2f    vec2f_mul_f(t_vec2f a, float b);
t_vec2f    vec2f_div_f(t_vec2f a, float b);

t_vec2f    vec2f_add_v(t_vec2f a, t_vec2f b);
t_vec2f    vec2f_sub_v(t_vec2f a, t_vec2f b);
t_vec2f    vec2f_mul_v(t_vec2f a, t_vec2f b);
t_vec2f    vec2f_div_v(t_vec2f a, t_vec2f b);

#endif