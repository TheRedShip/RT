/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:42:16 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 21:42:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_material(t_scene *scene, char *str, t_material *material)
{
	char		**split;

	split = ft_split(str, ',');
	if (!split)
		return (-1);
	material->roughness = ft_atof(split[0]);
	material->specular_probs = ft_atof(split[1]);
	if (ft_tab_len(split) == 3 && ft_atoi(split[2]) == 1)
		material->checkered = 1;
	if (ft_tab_len(split) == 4)
		init_texture(scene, material, split[3]);
	ft_free_tab((void **)(split));
	return (1);
}

void	setup_quad(t_objects *o[6], char **s, int j)
{
	o[j]->origin = rt_atof3(s[1], -1000.0, 1000.0);
	o[j]->quad->right_corner = (t_vec3f){0, ft_atof(s[3]), 0};
	o[j]->quad->up_corner = (t_vec3f){ft_atof(s[2]), 0, 0};
	if (j == 0)
		o[j]->quad->up_corner = (t_vec3f){0, 0, -ft_atof(s[2])};
	if (j == 0)
		o[j]->quad->right_corner = (t_vec3f){ft_atof(s[2]), 0, 0};
	if (j == 2)
		o[j]->origin = v_add_v(o[j]->origin, (t_vec3f){0, 0, -ft_atof(s[2])});
	if (j == 2)
		o[j]->quad->up_corner = (t_vec3f){0, 0, ft_atof(s[2])};
	if (j == 3)
		o[j]->origin = v_add_v(o[j]->origin, (t_vec3f){ft_atof(s[2]), 0, 0});
	if (j == 3)
		o[j]->quad->up_corner = (t_vec3f){0, 0, -ft_atof(s[2])};
	if (j == 4)
		o[j]->origin = v_add_v(o[j]->origin, \
					(t_vec3f){ft_atof(s[2]), 0, -ft_atof(s[2])});
	if (j == 4)
		o[j]->quad->up_corner = (t_vec3f){-ft_atof(s[2]), 0, 0};
	if (j == 5)
		o[j]->origin = v_add_v(o[j]->origin, (t_vec3f){0, ft_atof(s[3]), 0});
	if (j == 5)
		o[j]->quad->right_corner = (t_vec3f){0, 0, -ft_atof(s[2])};
}

void	calculate_up_right(t_vec3f normal, t_vec3f *up, t_vec3f *right)
{
	t_vec3f	temp_up;
	float	dot_product;
	t_vec3f	projected_up;

	temp_up = (t_vec3f){0, 2, 0};
	normal = normalize(normal);
	dot_product = v_dot(temp_up, normal);
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

void	link_portals(t_scene *scene)
{
	t_objects	*obj;
	t_objects	*tmp;
	t_objects	*start;

	obj = scene->objects;
	start = obj;
	while (obj)
	{
		if (obj->type == OBJ_PORTA)
		{
			tmp = start;
			while (tmp && !obj->portal->linked_portal)
			{
				if (tmp->type == OBJ_PORTA
					&& obj->portal->linked_id == tmp->portal->portal_id)
					obj->portal->linked_portal = tmp;
				tmp = tmp->next;
			}
		}
		obj = obj->next;
	}
}
