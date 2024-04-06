/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:34:14 by marvin            #+#    #+#             */
/*   Updated: 2024/04/06 19:34:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitInfo	hit_sphere(t_ray ray, t_objects *obj, t_sphere *sphere)
{
	float		a;
	float		b;
	float		c;
	t_hitInfo	hit_info;
	float		discriminant;
	a = vec3f_dot_v(ray.direction, ray.direction);
	b = (2*ray.origin.x*ray.direction.x - 2*ray.direction.x*obj->origin.x) + 
				(2*ray.origin.y*ray.direction.y - 2*ray.direction.y*obj->origin.y) + 
				(2*ray.origin.z*ray.direction.z - 2*ray.direction.z*obj->origin.z);
	c = (ray.origin.x*ray.origin.x - 2*ray.origin.x*obj->origin.x + obj->origin.x*obj->origin.x) + 
				(ray.origin.y*ray.origin.y - 2*ray.origin.y*obj->origin.y + obj->origin.y*obj->origin.y) + 
				(ray.origin.z*ray.origin.z - 2*ray.origin.z*obj->origin.z + obj->origin.z*obj->origin.z) - 
				(sphere->diameter / 2 * sphere->diameter / 2);
	//a = vec3f_dot_v(ray.direction, ray.direction);
	//b = 2.0f * vec3f_dot_v(ray.origin, ray.direction);
	//c = vec3f_dot_v(ray.origin, ray.origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	
	discriminant = b*b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		hit_info.distance = -1.0f;
		return (hit_info);
	}
	hit_info.distance = (-b - sqrt(discriminant)) / (2.0f * a);
	if (hit_info.distance < 0.0f)
		hit_info.distance = (-b + sqrt(discriminant)) / (2.0f * a);
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, hit_info.distance));
	hit_info.normal = normalize(vec3f_sub_v(hit_info.position, obj->origin));
	return (hit_info);
}

t_hitInfo		hit_plane(t_ray ray, t_objects *obj, t_plane *plane)
{
	t_hitInfo	hit_info;
	float		denom;

	denom = vec3f_dot_v(plane->normal, ray.direction);
	if (denom == 0)
	{
		hit_info.distance = -1.0f;
		return (hit_info);
	} 
	hit_info.distance = vec3f_dot_v(vec3f_sub_v(obj->origin, ray.origin), plane->normal) / denom;
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, hit_info.distance));
	hit_info.normal = plane->normal;
	return (hit_info);
}

t_hitInfo		hit_objects(t_ray ray, t_objects *obj)
{
	t_hitInfo	hit_info;

	if (obj->type == OBJ_SPHER)
		return (hit_sphere(ray, obj, obj->sphere));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane(ray, obj, obj->plane));
	hit_info.distance = -1.0f;
	return (hit_info);
}