/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:02 by ycontre           #+#    #+#             */
/*   Updated: 2024/05/02 15:09:04 by ycontre          ###   ########.fr       */
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

t_boundary	get_boundary(t_objects *object)
{
	if (object->type == OBJ_SPHER)
		return get_sphere_boundary(object);
	// else if (object->type == OBJ_QUADS)
	// 	return get_quad_boundary(object);
	// else if (object->type == OBJ_CYLIN)
	// 	return get_cylinder_boundary(object);
	// else if (object->type == OBJ_PLANE)
	// 	return get_plane_boundary(object);
	// else if (object->type == OBJ_ELLIP)
		// return get_ellipse_boundary(object);
	return (t_boundary){(t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}};
}