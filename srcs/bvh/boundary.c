/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:20:07 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 23:20:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boundary	get_sphere_boundary(t_objects *object)
{
	t_boundary	boundary;

	boundary.origin = v_add_f(object->origin, -object->sphere->diameter / 2);
	boundary.size = (t_vec3f){object->sphere->diameter, \
								object->sphere->diameter, \
								object->sphere->diameter};
	return (boundary);
}

t_boundary	get_quad_boundary(t_objects *obj)
{
	t_boundary	boundary;

	boundary.origin = v_sub_v(obj->origin, obj->quad->normal);
	boundary.size = v_add_v(\
					v_add_v(obj->quad->right_corner, obj->quad->up_corner), \
					v_mul_f(obj->quad->normal, 2.0f));
	return (boundary);
}

t_boundary	get_triangle_boundary(t_objects *o)
{
	t_boundary	b;

	b.origin = (t_vec3f){fmin(fmin(o->origin.x, o->triangle->pb.x), \
									o->triangle->pc.x),
		fmin(fmin(o->origin.y, o->triangle->pb.y), o->triangle->pc.y),
		fmin(fmin(o->origin.z, o->triangle->pb.z), o->triangle->pc.z)};
	b.size = (t_vec3f){fmax(fmax(o->origin.x, o->triangle->pb.x), \
									o->triangle->pc.x),
		fmax(fmax(o->origin.y, o->triangle->pb.y), o->triangle->pc.y),
		fmax(fmax(o->origin.z, o->triangle->pb.z), o->triangle->pc.z)};
	b.size = v_sub_v(b.size, b.origin);
	return (b);
}

t_boundary	get_boundary(t_objects *object)
{
	if (object->type == OBJ_SPHER)
		return (get_sphere_boundary(object));
	else if (object->type == OBJ_QUADS)
		return (get_quad_boundary(object));
	else if (object->type == OBJ_TRIAN)
		return (get_triangle_boundary(object));
	return ((t_boundary){(t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}});
}
