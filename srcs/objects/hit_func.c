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
	a = vec3f_dot(ray.direction, ray.direction);
	b = (2*ray.origin.x*ray.direction.x - 2*ray.direction.x*obj->origin.x) + 
				(2*ray.origin.y*ray.direction.y - 2*ray.direction.y*obj->origin.y) + 
				(2*ray.origin.z*ray.direction.z - 2*ray.direction.z*obj->origin.z);
	c = (ray.origin.x*ray.origin.x - 2*ray.origin.x*obj->origin.x + obj->origin.x*obj->origin.x) + 
				(ray.origin.y*ray.origin.y - 2*ray.origin.y*obj->origin.y + obj->origin.y*obj->origin.y) + 
				(ray.origin.z*ray.origin.z - 2*ray.origin.z*obj->origin.z + obj->origin.z*obj->origin.z) - 
				(sphere->diameter / 2 * sphere->diameter / 2);
	

	//a = vec3f_dot(ray.direction, ray.direction);
	//b = 2.0f * vec3f_dot(ray.origin, ray.direction);
	//c = vec3f_dot(ray.origin, ray.origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	
	a = vec3f_dot(ray.direction, ray.direction);

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

	denom = vec3f_dot(plane->normal, ray.direction);
	if (denom == 0)
	{
		hit_info.distance = -1.0f;
		return (hit_info);
	} 
	hit_info.distance = vec3f_dot(vec3f_sub_v(obj->origin, ray.origin), plane->normal) / denom;
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, hit_info.distance));
	hit_info.normal = plane->normal;
	return (hit_info);
}

t_hitInfo		hit_quad(t_ray ray, t_objects *obj, t_quad *quad)
{
	float		denom;
	float		beta;
	float		alpha;
	t_hitInfo	hit_info;
	t_vec3f		planar_hitpt_vector;

	denom = vec3f_dot(quad->normal, ray.direction);
	hit_info.distance = -1.0f;
	if (fabs(denom) < 1e-8)
		return (hit_info);
	hit_info.distance = (quad->d - vec3f_dot(ray.origin, quad->normal)) / denom;
	if (hit_info.distance < 0.0f)
		return (hit_info);
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, hit_info.distance));
	//hit_info.normal = vec3f_mul_f(quad->normal, -ft_sign(denom));
	hit_info.normal = quad->normal;
	planar_hitpt_vector = vec3f_sub_v(hit_info.position, obj->origin);
	alpha = vec3f_dot(quad->w, vec3f_cross(planar_hitpt_vector, normalize(quad->right_corner)));
	beta = vec3f_dot(quad->w, vec3f_cross(normalize(quad->up_corner), planar_hitpt_vector));
	if (alpha < 0 || beta < 0 || alpha > vec3f_length(quad->up_corner) || beta > vec3f_length(quad->right_corner))
	{
		hit_info.distance = -1.0f;
		return hit_info;
	}
	return (hit_info);
}

t_hitInfo		hit_objects(t_ray ray, t_objects *obj)
{
	t_hitInfo	hit_info;

	if (obj->type == OBJ_SPHER)
		return (hit_sphere(ray, obj, obj->sphere));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane(ray, obj, obj->plane));
	else if (obj->type == OBJ_QUADS)
		return (hit_quad(ray, obj, obj->quad));
	hit_info.distance = -1.0f;
	return (hit_info);
}