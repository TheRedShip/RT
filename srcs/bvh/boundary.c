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
	boundary.size = (t_vec3f){object->sphere->diameter, object->sphere->diameter, object->sphere->diameter};
	return (boundary);
}

t_boundary	get_quad_boundary(t_objects *object)
{
	t_boundary	boundary;
	
	boundary.origin = v_sub_v(object->origin, object->quad->normal);
	boundary.size = v_add_v(v_add_v(object->quad->right_corner, object->quad->up_corner), \
								v_mul_f(object->quad->normal, 2.0f));
	return (boundary);
}

t_boundary get_cylinder_boundary(t_objects *object) {
    t_boundary boundary;
    t_vec3f pa;
    t_vec3f pb;

    pa = object->origin;
    pb = v_add_v(object->origin, v_mul_f(object->cylinder->orientation, object->cylinder->height));

    t_vec3f a = v_sub_v(pb, pa);
    t_vec3f test = v_sub_v((t_vec3f){1.0f, 1.0f, 1.0f}, v_div_f(v_mul_v(a, a), v_dot(a, a)));
    t_vec3f e = v_mul_f((t_vec3f){sqrt(test.x), sqrt(test.y), sqrt(test.z)}, object->cylinder->diameter / 2);
    t_vec3f e_bis = v_mul_f((t_vec3f){sqrt(test.x), sqrt(test.y), sqrt(test.z)}, object->cylinder->diameter);

    t_vec3f first_origin = v_sub_v(pa, e);
    t_vec3f second_origin = v_add_v(pb, e);

    boundary.origin = (t_vec3f){fmin(first_origin.x, second_origin.x), fmin(first_origin.y, second_origin.y), fmin(first_origin.z, second_origin.z)};

    t_vec3f first_size = v_sub_v(pa, e_bis);
    t_vec3f second_size = v_add_v(pb, e_bis);

    boundary.size = (t_vec3f){fmax(first_size.x, second_size.x), fmax(first_size.y, second_size.y), fmax(first_size.z, second_size.z)};
    
    return boundary;
}

t_boundary	get_triangle_boundary(t_objects *object)
{
	t_boundary	boundary;

	boundary.origin = (t_vec3f){fmin(fmin(object->origin.x, object->triangle->pb.x), object->triangle->pc.x),
								fmin(fmin(object->origin.y, object->triangle->pb.y), object->triangle->pc.y),
								fmin(fmin(object->origin.z, object->triangle->pb.z), object->triangle->pc.z)};
	boundary.size = (t_vec3f){fmax(fmax(object->origin.x, object->triangle->pb.x), object->triangle->pc.x),
								fmax(fmax(object->origin.y, object->triangle->pb.y), object->triangle->pc.y),
								fmax(fmax(object->origin.z, object->triangle->pb.z), object->triangle->pc.z)};
	boundary.size = v_sub_v(boundary.size, boundary.origin);
	return (boundary);

}

t_boundary	get_boundary(t_objects *object)
{
	if (object->type == OBJ_SPHER)
		return get_sphere_boundary(object);
	else if (object->type == OBJ_QUADS)
		return get_quad_boundary(object);
	else if (object->type == OBJ_CYLIN)
		return get_cylinder_boundary(object);
	else if (object->type == OBJ_TRIAN)
		return get_triangle_boundary(object);
	// else if (object->type == OBJ_ELLIP)
	// 	return get_ellipse_boundary(object);
	return (t_boundary){(t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}};
}