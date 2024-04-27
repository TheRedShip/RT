/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bounding_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:30:33 by marvin            #+#    #+#             */
/*   Updated: 2024/04/27 17:30:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boundary	get_sphere_boundary(t_objects *object)
{
	t_boundary	boundary;

	boundary.origin = vec3f_add_f(object->origin, -object->sphere->diameter / 2);
	boundary.size = (t_vec3f){object->sphere->diameter, object->sphere->diameter, object->sphere->diameter};
	return (boundary);
}

t_boundary	get_quad_boundary(t_objects *object)
{
	t_boundary	boundary;

	boundary.origin = object->origin;
	boundary.size = vec3f_add_v(object->quad->right_corner, object->quad->up_corner);
	return (boundary);
}

t_boundary get_cylinder_boundary(t_objects *object) {
    t_boundary boundary;
    t_vec3f pa;
    t_vec3f pb;

    pa = object->origin;
    pb = vec3f_add_v(object->origin, vec3f_mul_f(object->cylinder->orientation, object->cylinder->height));

    t_vec3f a = vec3f_sub_v(pb, pa);
    t_vec3f test = vec3f_sub_v((t_vec3f){1.0f, 1.0f, 1.0f}, vec3f_div_f(vec3f_mul_v(a, a), vec3f_dot(a, a)));
    t_vec3f e = vec3f_mul_f((t_vec3f){sqrt(test.x), sqrt(test.y), sqrt(test.z)}, object->cylinder->diameter / 2);
    t_vec3f e_bis = vec3f_mul_f((t_vec3f){sqrt(test.x), sqrt(test.y), sqrt(test.z)}, object->cylinder->diameter);

    t_vec3f first_origin = vec3f_sub_v(pa, e);
    t_vec3f second_origin = vec3f_add_v(pb, e);

    boundary.origin = (t_vec3f){fmin(first_origin.x, second_origin.x), fmin(first_origin.y, second_origin.y), fmin(first_origin.z, second_origin.z)};

    t_vec3f first_size = vec3f_sub_v(pa, e_bis);
    t_vec3f second_size = vec3f_add_v(pb, e_bis);

    boundary.size = (t_vec3f){fmax(first_size.x, second_size.x), fmax(first_size.y, second_size.y), fmax(first_size.z, second_size.z)};
    
    return boundary;
}

t_boundary	get_boundary(t_objects *object)
{
	if (object->type == OBJ_SPHER)
		return get_sphere_boundary(object);
	else if (object->type == OBJ_QUADS)
		return get_quad_boundary(object);
	else if (object->type == OBJ_CYLIN)
		return get_cylinder_boundary(object);
	// else if (object->type == OBJ_ELLIP)
		// return get_ellipse_boundary(object);
	return (t_boundary){(t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}};
}