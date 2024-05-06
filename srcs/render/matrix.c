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
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);

	matrix[0][0] = 1.0f;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;

	matrix[1][0] = 0.0f;
	matrix[1][1] = cosTheta;
	matrix[1][2] = -sinTheta;

	matrix[2][0] = 0.0f;
	matrix[2][1] = sinTheta;
	matrix[2][2] = cosTheta;
}

void	apply_rotation_matrix_y(float angle, float (*matrix)[3])
{
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);

	matrix[0][0] = cosTheta;
	matrix[0][1] = 0.0f;
	matrix[0][2] = -sinTheta;

	matrix[1][0] = 0.0f;
	matrix[1][1] = 1.0f;
	matrix[1][2] = 0.0f;

	matrix[2][0] = sinTheta;
	matrix[2][1] = 0.0f;
	matrix[2][2] = cosTheta;
}

void	multiplyMatrixVector(float (*matrix)[3], t_vec3f vector, t_vec3f *result)
{
	result->x = matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2] * vector.z;
	result->y = matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2] * vector.z;
	result->z = matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2] * vector.z;
}

t_vec3f		calculate_ray_direction(t_scene *scene, t_vec3f prev)
{
	t_vec3f			result;
	float	calcul;

	calcul = tan(scene->camera->fov / 2.0f * M_PI / 180.0f);
	prev.x *= calcul;
	prev.y *= calcul;
	multiplyMatrixVector(scene->camera->rotation_matrix_x, prev, &result);
	multiplyMatrixVector(scene->camera->rotation_matrix_y, result, &result);
	result = normalize(result);
	return (result);
}
