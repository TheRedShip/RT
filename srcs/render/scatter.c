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

t_ray	lambert_ray(t_hit_info hit, t_ray ray, \
					t_threads *thread, int *is_specular)
{
	t_vec3f	in_unit_sphere;
	t_vec3f	diffuse_dir;
	t_vec3f	specular_dir;

	in_unit_sphere = (t_vec3f){ft_random(thread->id, -1.0f, 1.0f), \
								ft_random(thread->id, -1.0f, 1.0f), \
								ft_random(thread->id, -1.0f, 1.0f)};
	in_unit_sphere = normalize(in_unit_sphere);
	if (v_dot(in_unit_sphere, hit.normal) < 0.0)
		in_unit_sphere = v_mul_f(in_unit_sphere, -1.0f);
	diffuse_dir = normalize(v_add_v(hit.normal, in_unit_sphere));
	specular_dir = reflect(ray.direction, hit.normal);
	*is_specular = 1;
	if (hit.obj->material.specular_probs > 0.0f && \
		hit.obj->material.specular_probs > ft_random(thread->id, 0.0f, 1.0f))
		*is_specular = 0;
	ray.origin = v_add_v(hit.position, v_mul_f(hit.normal, 0.0001f));
	ray.direction = lerp(diffuse_dir, specular_dir, \
					hit.obj->material.roughness * (*is_specular));
	return (ray);
}

t_ray	dielectric_ray(t_hit_info hit_info, t_ray ray)
{
	float	refraction_ratio;
	t_vec3f	unit_direction;

	if (v_dot(ray.direction, hit_info.normal) > 0.0f)
	{
		hit_info.normal = v_mul_f(hit_info.normal, -1.0f);
		refraction_ratio = hit_info.obj->material.refraction_index;
	}
	else
		refraction_ratio = 1.0f / hit_info.obj->material.refraction_index;
	unit_direction = normalize(ray.direction);
	ray.origin = v_add_v(hit_info.position, v_mul_f(hit_info.normal, -0.0001f));
	ray.direction = refract(unit_direction, hit_info.normal, refraction_ratio);
	return (ray);
}

t_ray	portal_ray(t_scene *scene, t_hit_info *hit, t_ray ray)
{
	t_vec3f	portal_offset;
	t_vec3f	cross;

	if (hit->obj->portal->linked_portal == NULL)
		return (ray);
	portal_offset = v_sub_v(hit->obj->portal->linked_portal->origin, \
							hit->obj->origin);
	ray.origin = v_add_v(hit->position, portal_offset);
	if (v_dot(ray.direction, \
			hit->obj->portal->linked_portal->portal->quad.normal) < 0.0f)
		ray.direction = reflect(ray.direction, \
						hit->obj->portal->linked_portal->portal->quad.normal);
	else
	{
		cross = v_cross(hit->obj->portal->linked_portal->portal->quad.up_corner,
				hit->obj->portal->linked_portal->portal->quad.normal);
		cross = v_mul_f(normalize(cross), 2.0f);
		ray.origin = v_sub_v(ray.origin, cross);
	}
	ray.origin = v_add_v(ray.origin, \
		v_mul_f(hit->obj->portal->linked_portal->portal->quad.normal, 0.0001f));
	*hit = trace_ray(scene, ray);
	return (ray);
}

t_ray	new_ray(t_hit_info hit_info, t_ray ray, \
					t_threads *thread, int *is_specular)
{
	*is_specular = 1;
	if (hit_info.obj->material.type == MAT_LAMBERT)
		return (lambert_ray(hit_info, ray, thread, is_specular));
	else if (hit_info.obj->material.type == MAT_DIELECTRIC)
		return (dielectric_ray(hit_info, ray));
	return (ray);
}
