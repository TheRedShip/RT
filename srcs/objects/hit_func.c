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

int	triangle_test(t_hit_info hit_info, t_triangle *tri, t_objects *obj, int abc)
{
	t_vec3f		diff;
	t_vec3f		vert;
	float		test;

	if (abc == 0)
		vert = obj->origin;
	else if (abc == 1)
		vert = tri->pb;
	else
		vert = tri->pc;
	diff = v_sub_v(hit_info.position, vert);
	test = v_dot(tri->normal, v_cross(tri->edge[abc], diff));
	return (test >= 0);
}

t_hit_info	hit_triangle(t_ray ray, t_objects *obj, t_triangle *tri)
{
	t_hit_info	h;
	float		pl;

	h.distance = -1.0f;
	pl = v_dot(tri->normal, ray.direction);
	if (fabs(pl) < 0)
		return (h);
	h.distance = -(v_dot(tri->normal, ray.origin) + tri->traverse) / pl;
	if (h.distance < 0)
		return (h);
	h.position = v_add_v(ray.origin, v_mul_f(ray.direction, h.distance));
	if (!triangle_test(h, tri, obj, 0)
		|| !triangle_test(h, tri, obj, 1)
		|| !triangle_test(h, tri, obj, 2))
	{
		h.distance = -1.0f;
		return (h);
	}
	h.normal = tri->normal;
	if (pl > 0)
		h.normal = v_mul_f(h.normal, -1);
	return (h);
}

t_hit_info	hit_objects(t_ray ray, t_objects *obj)
{
	t_hit_info	hit_info;

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
	else if (obj->type == OBJ_PORTA)
		return (hit_quad(ray, obj, &obj->portal->quad));
	else if (obj->type == OBJ_TRIAN)
		return (hit_triangle(ray, obj, obj->triangle));
	hit_info.distance = -1.0f;
	return (hit_info);
}
