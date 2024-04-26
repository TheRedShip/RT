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
	
	// ray.origin = vec3f_sub_v(ray.origin, obj->origin);
	// a = vec3f_dot(ray.direction, ray.direction);
	// b = 2.0f * vec3f_dot(ray.origin, ray.direction);
	// c = vec3f_dot(ray.origin, ray.origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	// ray.origin = vec3f_add_v(ray.origin, obj->origin);
	
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

t_hitInfo		hit_ellipse(t_ray ray, t_objects *obj, t_ellipse *ellipse)
{
	// x^2/a^2 + y^2/b^2 + z^2/c^2 = r
	// x = x0 + t * dx
	// y = y0 + t * dy
	// z = z0 + t * dz
	// (x0 + t * dx)^2/a^2 + (y0 + t * dy)^2/b^2 + (z0 + t * dz)^2/c^2 = r
	// x0^2/a^2 + 2 * x0 * t * dx/a^2 + t^2 * dx^2/a^2 + y0^2/b^2 + 2 * y0 * t * dy/b^2 + t^2 * dy^2/b^2 + z0^2/c^2 + 2 * z0 * t * dz/c^2 + t^2 * dz^2/c^2 = r
	// t^2 * (dx^2/a^2 + dy^2/b^2 + dz^2/c^2) + t * (2 * x0 * dx/a^2 + 2 * y0 * dy/b^2 + 2 * z0 * dz/c^2) + (x0^2/a^2 + y0^2/b^2 + z0^2/c^2 - r) = 0
	// a = dx^2/a^2 + dy^2/b^2 + dz^2/c^2
	// b = 2 * x0 * dx/a^2 + 2 * y0 * dy/b^2 + 2 * z0 * dz/c^2
	// c = x0^2/a^2 + y0^2/b^2 + z0^2/c^2 - r
	float		a;
	float		b;
	float		c;
	t_hitInfo	hit_info;
	float		discriminant;
	
	ray.origin = vec3f_sub_v(ray.origin, obj->origin);
	a = ray.direction.x * ray.direction.x / (ellipse->a * ellipse->a) + ray.direction.y * ray.direction.y / (ellipse->b * ellipse->b) + ray.direction.z * ray.direction.z / (ellipse->c * ellipse->c);
	b = 2.0f * ray.origin.x * ray.direction.x / (ellipse->a * ellipse->a) + 2.0f * ray.origin.y * ray.direction.y / (ellipse->b * ellipse->b) + 2.0f * ray.origin.z * ray.direction.z / (ellipse->c * ellipse->c);
	c = ray.origin.x * ray.origin.x / (ellipse->a * ellipse->a) + ray.origin.y * ray.origin.y / (ellipse->b * ellipse->b) + ray.origin.z * ray.origin.z / (ellipse->c * ellipse->c) - 1.0f;
	ray.origin = vec3f_add_v(ray.origin, obj->origin);

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
	planar_hitpt_vector = vec3f_sub_v(hit_info.position, obj->origin);
	alpha = vec3f_dot(quad->w, vec3f_cross(planar_hitpt_vector, normalize(quad->right_corner)));
	beta = vec3f_dot(quad->w, vec3f_cross(normalize(quad->up_corner), planar_hitpt_vector));
	if (alpha < 0 || beta < 0 || alpha > vec3f_length(quad->up_corner) || beta > vec3f_length(quad->right_corner))
	{
		hit_info.distance = -1.0f;
		return hit_info;
	}
	hit_info.normal = vec3f_mul_f(quad->normal, -ft_sign(denom));
	return (hit_info);
}

t_hitInfo		hit_cylinder(t_ray ray, t_objects *obj, t_cylinder *cylinder)
{
	t_hitInfo	hit_info;

	t_vec3f tmp1 = vec3f_cross(ray.direction, cylinder->orientation);
	t_vec3f	tmp_vect = vec3f_sub_v(ray.origin, obj->origin);
	t_vec3f	tmp2 = vec3f_cross(tmp_vect, cylinder->orientation);
	
	float	a = vec3f_dot(tmp1, tmp1);
	float	b = 2.0 * vec3f_dot(tmp1, tmp2);
	float	c = vec3f_dot(tmp2, tmp2) - (cylinder->diameter / 2.0) * (cylinder->diameter / 2.0);
	float	discriminant = b*b - 4.0 * a * c;

	float	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	float	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > t2)
	{
		float tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	t_vec3f	mid_vect = vec3f_mul_f(cylinder->orientation, (cylinder->height / 2.0));
	t_vec3f	mid_point = vec3f_add_v(obj->origin, mid_vect);
	float	tmp1_bis = vec3f_dot(vec3f_sub_v(mid_point, ray.origin), cylinder->orientation);
	float	tmp2_bis = vec3f_dot(ray.direction, cylinder->orientation);
	float	t3 = (tmp1_bis + (cylinder->height / 2.0)) / tmp2_bis;
	float	t4 = (tmp1_bis - (cylinder->height / 2.0)) / tmp2_bis;
	if (t3 > t4)
	{
		float tmp = t3;
		t3 = t4;
		t4 = tmp;
	}
	if (t3 > t2 || t4 < t1)
	{
		hit_info.distance = -1.0f;
		return (hit_info);
	}
	float	t_final = fmax(t1, t3);
	if (t_final < 0)
		t_final = fmin(t2, t4);
	if (t_final <= 0)
	{
		hit_info.distance = -1.0f;
		return (hit_info);
	}

	hit_info.distance = t_final;
	hit_info.position = vec3f_add_v(ray.origin, vec3f_mul_f(ray.direction, hit_info.distance));
	if (t3 < t1)
		hit_info.normal = normalize(vec3f_sub_v(vec3f_sub_v(hit_info.position, obj->origin), vec3f_mul_f(cylinder->orientation, vec3f_dot(vec3f_sub_v(hit_info.position, obj->origin), cylinder->orientation))));
	else
		hit_info.normal = vec3f_mul_f(cylinder->orientation, -ft_sign(vec3f_dot(ray.direction, cylinder->orientation)));
	return (hit_info);
}

t_hitInfo		hit_objects(t_ray ray, t_objects *obj)
{
	t_hitInfo	hit_info;

	if (obj->type == OBJ_SPHER)
		return (hit_sphere(ray, obj, obj->sphere));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane(ray, obj, obj->plane));
	else if (obj->type == OBJ_CYLIN)
		return (hit_cylinder(ray, obj, obj->cylinder));
	else if (obj->type == OBJ_QUADS)
		return (hit_quad(ray, obj, obj->quad));
	else if (obj->type == OBJ_ELLIP)
		return (hit_ellipse(ray, obj, obj->ellipse));
	else if (obj->type == OBJ_PORTAL)
		return (hit_quad(ray, obj, &obj->portal->quad));
	hit_info.distance = -1.0f;
	return (hit_info);
}