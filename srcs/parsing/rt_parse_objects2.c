/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_objects2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 00:29:38 by marvin            #+#    #+#             */
/*   Updated: 2024/04/09 19:42:02 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_lightquad(char *line, t_scene *scene)
{
	t_objects	*objects;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	objects = rt_add_objects(scene, "qd");
	objects->origin = rt_atof3(s[1], -1000.0, 1000.0);
	objects->quad->right_corner = rt_atof3(s[2], -1000.0, 1000.0);
	objects->quad->up_corner = rt_atof3(s[3], -1000.0, 1000.0);
	objects->material.color = vec3f_div_f(rt_atof3(s[4], 0.0f, 255.0f), 255.0f);
	objects->material.emission_power = ft_atof(s[5]);
	objects->quad->normal = normalize(vec3f_cross(objects->quad->up_corner, \
							objects->quad->right_corner));
	objects->quad->d = vec3f_dot(objects->quad->normal, objects->origin);
	objects->quad->w = vec3f_div_f(objects->quad->normal, \
					vec3f_dot(objects->quad->normal, objects->quad->normal));
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_ellipse(char *line, t_scene *scene)
{
	char		**s;
	t_vec3f		radius;
	t_objects	*objects;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	objects = rt_add_objects(scene, "el");
	objects->origin = rt_atof3(s[1], -1000.0, 1000.0);
	radius = rt_atof3(s[2], 0.0, 10000.0);
	objects->ellipse->a = radius.x;
	objects->ellipse->b = radius.y;
	objects->ellipse->c = radius.z;
	objects->material.color = vec3f_div_f(rt_atof3(s[3], 0.0f, 255.0f), 255.0f);
	if (rt_parse_material(scene, s[4], &(objects->material)) == -1)
		return (rt_return (s));
	ft_free_tab((void **)(s));
	return (1);
}

void	calculate_up_right(t_vec3f normal, t_vec3f *up, t_vec3f *right)
{
	t_vec3f	temp_up;
	float	dot_product;
	t_vec3f	projected_up;

	temp_up = (t_vec3f){0, 2, 0};
	normal = normalize(normal);
	dot_product = vec3f_dot(temp_up, normal);
	projected_up = (t_vec3f){temp_up.x - dot_product * normal.x, \
							temp_up.y - dot_product * normal.y, \
							temp_up.z - dot_product * normal.z};
	projected_up = normalize(projected_up);
	*up = projected_up;
	right->x = normal.y * projected_up.z - normal.z * projected_up.y;
	right->y = normal.z * projected_up.x - normal.x * projected_up.z;
	right->z = normal.x * projected_up.y - normal.y * projected_up.x;
	*right = normalize(*right);
}

void	scale_quad(t_vec3f *up, t_vec3f *right, t_vec3f *origin, t_vec2f size)
{
	up->x *= size.y;
	up->y *= size.y;
	up->z *= size.y;
	right->x *= size.x;
	right->y *= size.x;
	right->z *= size.x;
	origin->x -= (right->x + up->x) * 0.5;
	origin->y -= (right->y + up->y) * 0.5;
	origin->z -= (right->z + up->z) * 0.5;
}

int	rt_parse_portal(char *line, t_scene *scene)
{
	t_objects	*portal;
	t_objects	*support;
	char		**s;

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	support = rt_add_objects(scene, "qd");
	support->origin = rt_atof3(s[1], -1000.0, 1000.0);
	support->quad->normal = rt_atof3(s[2], -1.0, 1.0);
	calculate_up_right(support->quad->normal, &support->quad->up_corner, \
						&support->quad->right_corner);
	scale_quad(&support->quad->up_corner, &support->quad->right_corner, \
				&support->origin, (t_vec2f){3, 6});
	support->quad->d = vec3f_dot(support->quad->normal, support->origin);
	support->quad->w = vec3f_div_f(support->quad->normal, \
					vec3f_dot(support->quad->normal, support->quad->normal));
	support->material.color = vec3f_div_f(rt_atof3(s[5], 0, 255), 255);
	support->material.emission_power = 1.5;
	portal = rt_add_objects(scene, "po");
	portal->portal->portal_id = ft_atoi(s[3]);
	portal->portal->linked_id = ft_atoi(s[4]);
	portal->portal->quad.normal = rt_atof3(s[2], -1.0, 1.0);
	portal->origin = rt_atof3(s[1], -1000.0, 1000.0);
	portal->origin = vec3f_add_v(portal->origin, \
					vec3f_mul_f(portal->portal->quad.normal, 0.0001f));
	calculate_up_right(portal->portal->quad.normal, \
		&portal->portal->quad.up_corner, &portal->portal->quad.right_corner);
	scale_quad(&portal->portal->quad.up_corner, \
	&portal->portal->quad.right_corner, &portal->origin, (t_vec2f){2.5, 5.5});
	portal->portal->quad.d = \
					vec3f_dot(portal->portal->quad.normal, portal->origin);
	portal->portal->quad.w = vec3f_div_f(portal->portal->quad.normal, \
		vec3f_dot(portal->portal->quad.normal, portal->portal->quad.normal));
	ft_free_tab((void **)(s));
	return (1);
}
