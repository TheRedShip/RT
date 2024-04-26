/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:06:18 by marvin            #+#    #+#             */
/*   Updated: 2024/04/02 23:06:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotationMatrixX(float angle, float (*matrix)[3])
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

void	apply_rotationMatrixY(float angle, float (*matrix)[3])
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
	static float	calcul = -42;

	if (calcul == -42)
		calcul = tan(scene->camera->fov / 2.0f * M_PI / 180.0f);
	prev.x *= calcul;
	prev.y *= calcul;
	multiplyMatrixVector(scene->camera->rotationMatrixX, prev, &result);
	multiplyMatrixVector(scene->camera->rotationMatrixY, result, &result);
	result = normalize(result);
	return (result);
}