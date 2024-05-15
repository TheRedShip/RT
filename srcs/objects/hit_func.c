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

__always_inline
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

__always_inline
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

__always_inline
void	cylinder_get_distance(t_vec3f *tv, float *g, float *t, void **info)
{
	float	tmp1_f;

	tv[0] = v_cross(((t_ray *)info[0])->direction, \
		((t_cylinder *)info[2])->orientation);
	tv[1] = v_cross(v_sub_v(((t_ray *)info[0])->origin, \
		((t_objects *)info[1])->origin), ((t_cylinder *)info[2])->orientation);
	g[0] = v_dot(tv[0], tv[0]);
	g[1] = 2.0 * v_dot(tv[0], tv[1]);
	g[2] = v_dot(tv[1], tv[1]) - (((t_cylinder *)info[2])->diameter / 2.0) *\
		(((t_cylinder *)info[2])->diameter / 2.0);
	t[0] = (-g[1] - sqrt(g[1] * g[1] - 4.0 * g[0] * g[2])) / (2.0 * g[0]);
	t[1] = (-g[1] + sqrt(g[1] * g[1] - 4.0 * g[0] * g[2])) / (2.0 * g[0]);
	ft_swap(&t[0], &t[1], t[0] > t[1]);
	tmp1_f = v_dot(v_sub_v(v_add_v(((t_objects *)info[1])->origin, \
		v_mul_f(((t_cylinder *)info[2])->orientation, \
		(((t_cylinder *)info[2])->height / 2.0))), \
		((t_ray *)info[0])->origin), ((t_cylinder *)info[2])->orientation);
	t[2] = (tmp1_f + (((t_cylinder *)info[2])->height / 2)) \
		/ v_dot(((t_ray *)info[0])->direction, \
		((t_cylinder *)info[2])->orientation);
	t[3] = (tmp1_f - (((t_cylinder *)info[2])->height / 2)) \
		/ v_dot(((t_ray *)info[0])->direction, \
		((t_cylinder *)info[2])->orientation);
	ft_swap(&t[2], &t[3], t[2] > t[3]);
}

__always_inline
t_hit_info	hit_cylinder(t_ray ray, t_objects *o, t_cylinder *cy)
{
	t_hit_info	h;
	t_vec3f		tv[2];
	float		g[3];
	float		t[4];

	cylinder_get_distance(tv, g, t, (void *[3]){&ray, o, cy});
	h.distance = fmin(fmax(t[0], t[2]), fmin(t[1], t[3]));
	if (t[2] > t[1] || t[3] < t[0])
		h.distance = -1.0f;
	if (h.distance <= 0)
		return (h);
	h.position = v_add_v(ray.origin, v_mul_f(ray.direction, h.distance));
	if (t[2] < t[0])
		h.normal = normalize(v_sub_v(v_sub_v(h.position, o->origin), v_mul_f(\
	cy->orientation, v_dot(v_sub_v(h.position, o->origin), cy->orientation))));
	else
		h.normal = v_mul_f(cy->orientation, -ft_sign(v_dot(ray.direction, \
		cy->orientation)));
	return (h);
}

__always_inline
t_hit_info	hit_objects(t_ray ray, t_objects *obj)
{
	t_hit_info	hit_info;

	hit_info.distance = -1.0f;
	if (obj->type == OBJ_SPHER)
		hit_info = hit_sphere(ray, obj, obj->sphere);
	else if (obj->type == OBJ_PLANE)
		hit_info = hit_plane(ray, obj, obj->plane);
	else if (obj->type == OBJ_CYLIN)
		hit_info = hit_cylinder(ray, obj, obj->cylinder);
	else if (obj->type == OBJ_QUADS)
		hit_info = hit_quad(ray, obj, obj->quad);
	else if (obj->type == OBJ_ELLIP)
		hit_info = hit_ellipse(ray, obj, obj->ellipse);
	else if (obj->type == OBJ_PORTA)
		hit_info = hit_quad(ray, obj, &obj->portal->quad);
	else if (obj->type == OBJ_TRIAN)
		hit_info = hit_triangle(ray, obj, obj->triangle);
	if (hit_info.distance > 0.0f && obj->material.bump_map.exist == 1)
	{
		hit_info.obj = obj;
		hit_info.normal = get_bump_normal(hit_info, obj->material.bump_map);
	}
	return (hit_info);
}
