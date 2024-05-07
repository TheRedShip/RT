/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:06:18 by marvin            #+#    #+#             */
/*   Updated: 2024/05/02 14:57:16 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotation_matrix_x(float angle, float (*matrix)[3])
{
	float	cos_theta;
	float	sin_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	matrix[0][0] = 1.0f;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;
	matrix[1][0] = 0.0f;
	matrix[1][1] = cos_theta;
	matrix[1][2] = -sin_theta;
	matrix[2][0] = 0.0f;
	matrix[2][1] = sin_theta;
	matrix[2][2] = cos_theta;
}

void	apply_rotation_matrix_y(float angle, float (*matrix)[3])
{
	float	cos_theta;
	float	sin_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	matrix[0][0] = cos_theta;
	matrix[0][1] = 0.0f;
	matrix[0][2] = -sin_theta;
	matrix[1][0] = 0.0f;
	matrix[1][1] = 1.0f;
	matrix[1][2] = 0.0f;
	matrix[2][0] = sin_theta;
	matrix[2][1] = 0.0f;
	matrix[2][2] = cos_theta;
}

void	multiply_matrix_vector(float (*m)[3], t_vec3f vector, t_vec3f *result)
{
	result->x = m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z;
	result->y = m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z;
	result->z = m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z;
}

t_vec3f	calculate_ray_direction(t_scene *scene, t_vec3f prev)
{
	t_vec3f			result;
	float			calcul;

	calcul = tan(scene->camera->fov / 2.0f * M_PI / 180.0f);
	prev.x *= calcul;
	prev.y *= calcul;
	multiply_matrix_vector(scene->camera->rotation_matrix_x, prev, &result);
	multiply_matrix_vector(scene->camera->rotation_matrix_y, result, &result);
	result = normalize(result);
	return (result);
}
