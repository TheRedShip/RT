/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_func_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 01:55:00 by marvin            #+#    #+#             */
/*   Updated: 2024/05/13 14:26:43 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_info	hit_sphere(t_ray r, t_objects *obj, t_sphere *sp)
{
	float		a;
	float		b;
	float		c;
	t_hit_info	hit_info;
	float		discriminant;

	hit_info.distance = -1.0f;
	r.origin = v_sub_v(r.origin, obj->origin);
	a = v_dot(r.direction, r.direction);
	b = 2.0f * v_dot(r.origin, r.direction);
	c = v_dot(r.origin, r.origin) - (sp->diameter / 2) * (sp->diameter / 2);
	r.origin = v_add_v(r.origin, obj->origin);
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (hit_info);
	hit_info.distance = (-b - sqrt(discriminant)) / (2.0f * a);
	if (hit_info.distance < 0.0f)
		hit_info.distance = (-b + sqrt(discriminant)) / (2.0f * a);
	hit_info.position = v_add_v(r.origin, \
						v_mul_f(r.direction, hit_info.distance));
	hit_info.normal = normalize(v_sub_v(hit_info.position, obj->origin));
	return (hit_info);
}

t_hit_info	hit_ellipse(t_ray ray, t_objects *obj, t_ellipse *el)
{
	float		abc[3];
	t_hit_info	hit;
	float		discriminant;

	hit.distance = -1.0f;
	ray.origin = v_sub_v(ray.origin, obj->origin);
	abc[0] = ray.direction.x * ray.direction.x / (el->a * el->a) + \
		ray.direction.y * ray.direction.y / (el->b * el->b) + \
		ray.direction.z * ray.direction.z / (el->c * el->c);
	abc[1] = 2.0f * ray.origin.x * ray.direction.x / (el->a * el->a) + \
		2.0f * ray.origin.y * ray.direction.y / (el->b * el->b) + \
		2.0f * ray.origin.z * ray.direction.z / (el->c * el->c);
	abc[2] = ray.origin.x * ray.origin.x / (el->a * el->a) + \
		ray.origin.y * ray.origin.y / (el->b * el->b) + \
		ray.origin.z * ray.origin.z / (el->c * el->c) - 1.0f;
	ray.origin = v_add_v(ray.origin, obj->origin);
	discriminant = abc[1] * abc[1] - 4.0f * abc[0] * abc[2];
	if (discriminant < 0.0f)
		return (hit);
	hit.distance = (-abc[1] - sqrt(discriminant)) / (2.0f * abc[0]);
	if (hit.distance < 0.0f)
		hit.distance = (-abc[1] + sqrt(discriminant)) / (2.0f * abc[0]);
	hit.position = v_add_v(ray.origin, v_mul_f(ray.direction, hit.distance));
	hit.normal = normalize(v_sub_v(hit.position, obj->origin));
	return (hit);
}

t_hit_info	hit_plane(t_ray ray, t_objects *obj, t_plane *plane)
{
	t_hit_info	hit;
	float		denom;

	hit.distance = -1.0f;
	denom = v_dot(plane->normal, ray.direction);
	if (denom == 0)
		return (hit);
	hit.distance = v_dot(v_sub_v(obj->origin, ray.origin), \
						plane->normal) / denom;
	hit.position = v_add_v(ray.origin, v_mul_f(ray.direction, hit.distance));
	hit.normal = plane->normal;
	return (hit);
}

t_hit_info	hit_quad(t_ray ray, t_objects *obj, t_quad *quad)
{
	float		denom;
	float		beta;
	float		alpha;
	t_hit_info	hit;
	t_vec3f		planar;

	denom = v_dot(quad->normal, ray.direction);
	hit.distance = -1.0f;
	if (fabs(denom) < 0)
		return (hit);
	hit.distance = (quad->d - v_dot(ray.origin, quad->normal)) / denom;
	if (hit.distance < 0.0f)
		return (hit);
	hit.position = v_add_v(ray.origin, v_mul_f(ray.direction, hit.distance));
	planar = v_sub_v(hit.position, obj->origin);
	alpha = v_dot(quad->w, v_cross(planar, normalize(quad->right_corner)));
	beta = v_dot(quad->w, v_cross(normalize(quad->up_corner), planar));
	if (alpha < 0 || beta < 0 || alpha > v_length(quad->up_corner) || \
		beta > v_length(quad->right_corner))
	{
		hit.distance = -1.0f;
		return (hit);
	}
	hit.normal = v_mul_f(quad->normal, -ft_sign(denom));
	return (hit);
}
