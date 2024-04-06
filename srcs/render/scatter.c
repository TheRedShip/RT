/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:05:52 by marvin            #+#    #+#             */
/*   Updated: 2024/04/06 20:05:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray		lambert_ray(t_hitInfo hit_info, t_ray ray, t_threads *thread, int *is_specular)
{
	t_vec3f	in_unit_sphere;
	t_vec3f	diffuse_dir;
	t_vec3f	specular_dir;
	
	in_unit_sphere = (t_vec3f){ft_random(thread->id, -1.0f, 1.0f), \
								ft_random(thread->id, -1.0f, 1.0f), \
								ft_random(thread->id, -1.0f, 1.0f)};
	in_unit_sphere = normalize(in_unit_sphere);
	if (vec3f_dot(in_unit_sphere, hit_info.normal) < 0.0)
		in_unit_sphere = vec3f_mul_f(in_unit_sphere, -1.0f);
	
	diffuse_dir = normalize(vec3f_add_v(hit_info.normal, in_unit_sphere));
	specular_dir = reflect(ray.direction, hit_info.normal);
	
	*is_specular = 1;
	if (hit_info.obj->material.specular_probs > 0.0f && \
		hit_info.obj->material.specular_probs > ft_random(thread->id, 0.0f, 1.0f))
		*is_specular = 0;
	ray.origin = vec3f_add_v(hit_info.position, vec3f_mul_f(hit_info.normal, 0.0001f));
	ray.direction = lerp(diffuse_dir, specular_dir, hit_info.obj->material.roughness * (*is_specular));
	return (ray);
}

t_ray		dielectric_ray(t_hitInfo hit_info, t_ray ray)
{
	double	refraction_ratio;
	t_vec3f	unit_direction;
	
	if (vec3f_dot(ray.direction, hit_info.normal) > 0.0f)
	{
		hit_info.normal = vec3f_mul_f(hit_info.normal, -1.0f);
		refraction_ratio = hit_info.obj->material.refraction_index;
	}
	else
		refraction_ratio = 1.0f / hit_info.obj->material.refraction_index;
	unit_direction = normalize(ray.direction);
	ray.origin = vec3f_add_v(hit_info.position, vec3f_mul_f(hit_info.normal, -0.0001f));
	ray.direction = refract(unit_direction, hit_info.normal, refraction_ratio);
	return (ray);
}

t_ray		new_ray(t_hitInfo hit_info, t_ray ray, t_threads *thread, int *is_specular)
{
	*is_specular = 1;
	if (hit_info.obj->material.type == MAT_LAMBERT)
		return (lambert_ray(hit_info, ray, thread, is_specular));
	else if (hit_info.obj->material.type == MAT_DIELECTRIC)
		return (dielectric_ray(hit_info, ray));
	return (ray);
}
