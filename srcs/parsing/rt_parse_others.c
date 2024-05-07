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
	objects->material.color = v_div_f(rt_atof3(s[3], 0.0f, 255.0f), 255.0f);
	if (rt_parse_material(scene, s[4], &(objects->material)) == -1)
		return (rt_return (s));
	ft_free_tab((void **)(s));
	return (1);
}

int	rt_parse_cube(char *line, t_scene *scene)
{
	int			j;
	char		**s;
	t_objects	*o[6];

	s = ft_split(line, '\t');
	if (!s)
		return (0);
	j = 0;
	while (j < 6)
	{
		o[j] = rt_add_objects(scene, "qd");
		setup_quad(o, s, j);
		o[j]->quad->normal = normalize(v_cross(o[j]->quad->up_corner, \
										o[j]->quad->right_corner));
		o[j]->quad->d = v_dot(o[j]->quad->normal, o[j]->origin);
		o[j]->quad->w = v_div_f(o[j]->quad->normal, \
						v_dot(o[j]->quad->normal, o[j]->quad->normal));
		o[j]->material.color = v_div_f(rt_atof3(s[5], 0, 255), 255);
		if (rt_parse_material(scene, s[6], &(o[j]->material)) == -1)
			return (rt_return(s));
		j++;
	}
	ft_free_tab((void **)(s));
	return (1);
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
	support->quad->d = v_dot(support->quad->normal, support->origin);
	support->quad->w = v_div_f(support->quad->normal, \
					v_dot(support->quad->normal, support->quad->normal));
	support->material.color = v_div_f(rt_atof3(s[5], 0, 255), 255);
	support->material.emission_power = 1.5;
	portal = rt_add_objects(scene, "po");
	portal->portal->portal_id = ft_atoi(s[3]);
	portal->portal->linked_id = ft_atoi(s[4]);
	portal->portal->quad.normal = rt_atof3(s[2], -1.0, 1.0);
	portal->origin = rt_atof3(s[1], -1000.0, 1000.0);
	portal->origin = v_add_v(portal->origin, \
					v_mul_f(portal->portal->quad.normal, 0.0001f));
	calculate_up_right(portal->portal->quad.normal, \
		&portal->portal->quad.up_corner, &portal->portal->quad.right_corner);
	scale_quad(&portal->portal->quad.up_corner, \
	&portal->portal->quad.right_corner, &portal->origin, (t_vec2f){2.5, 5.5});
	portal->portal->quad.d = \
					v_dot(portal->portal->quad.normal, portal->origin);
	portal->portal->quad.w = v_div_f(portal->portal->quad.normal, \
		v_dot(portal->portal->quad.normal, portal->portal->quad.normal));
	ft_free_tab((void **)(s));
	return (1);
}
