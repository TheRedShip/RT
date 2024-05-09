/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:20:42 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 23:20:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	box_intersection(t_ray ray, t_vec3f origin, t_vec3f rad)
{
	t_vec3f	t[2];
	t_vec3f	m;
	t_vec3f	n;
	t_vec3f	k;
	float	t_f;

	ray.origin = v_sub_v(ray.origin, origin);
	m = (t_vec3f){1.0 / ray.direction.x, \
					1.0 / ray.direction.y, \
					1.0 / ray.direction.z};
	n = v_mul_f(v_mul_v(m, ray.origin), -1.0f);
	k = (t_vec3f){fabs(m.x) * rad.x, fabs(m.y) * rad.y, fabs(m.z) * rad.z};
	t[0] = v_sub_v(n, k);
	t[1] = v_add_v(n, k);
	ray.origin = v_add_v(ray.origin, origin);
	t_f = fmin(fmin(t[1].x, t[1].y), t[1].z);
	if (fmax(fmax(t[0].x, t[0].y), t[0].z) > t_f || t_f < 0.0)
		return (0);
	return (1);
}

int	boundary_intersect(t_boundary boundary, t_objects *object)
{
	float		tab1[3];
	float		tab2[3];
	float		tab3[3];
	float		tab4[3];
	t_boundary	obj_boundary;

	obj_boundary = get_boundary(object);
	tab1[0] = boundary.origin.x;
	tab1[1] = boundary.origin.y;
	tab1[2] = boundary.origin.z;
	tab2[0] = boundary.origin.x + boundary.size.x;
	tab2[1] = boundary.origin.y + boundary.size.y;
	tab2[2] = boundary.origin.z + boundary.size.z;
	tab3[0] = obj_boundary.origin.x;
	tab3[1] = obj_boundary.origin.y;
	tab3[2] = obj_boundary.origin.z;
	tab4[0] = obj_boundary.origin.x + obj_boundary.size.x;
	tab4[1] = obj_boundary.origin.y + obj_boundary.size.y;
	tab4[2] = obj_boundary.origin.z + obj_boundary.size.z;
	return (tab1[0] <= tab4[0] && tab2[0] >= tab3[0] && \
			tab1[1] <= tab4[1] && tab2[1] >= tab3[1] && \
			tab1[2] <= tab4[2] && tab2[2] >= tab3[2]);
}
