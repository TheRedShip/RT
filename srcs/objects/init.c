/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:23:35 by marvin            #+#    #+#             */
/*   Updated: 2024/03/31 21:42:14 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	init_material()
{
	t_material mat;

	mat.roughness = 1.0f;
	mat.metallic = 0.0;
	mat.color = (t_vec3f){0.0f, 0.0f, 0.0f};
	mat.emission_power = 0.0f;
	return (mat);
}

void	rt_set_objects_to_scene(t_scene *scene, t_objects *obj)
{
	t_objects *tmp;

	if (!scene->objects)
		scene->objects = obj;
	else
	{
		tmp = scene->objects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
}

t_objects	*rt_add_objects(t_scene **scene, char *type)
{
	t_objects *objects;
	static	char *type_list_str[4] = {"sp", "pl", "cy", NULL};
	int	i;

	objects = ft_calloc(1, sizeof(t_objects));
	if (!objects)
		rt_free_scene(*scene);
	i = -1;
	while (type_list_str[++i] != NULL)
	{
		if (!ft_strncmp(type, type_list_str[i], 2))
			break ;
	}
	objects->type = i;
	objects->material = init_material();
	rt_set_objects_to_scene(*scene, objects);
	if (i == 0)
		objects->sphere = ft_calloc(1, sizeof(t_sphere));
	else if (i == 1)
		objects->plane = ft_calloc(1, sizeof(t_plane));
	else if (i == 2)
		objects->cylinder = ft_calloc(1, sizeof(t_cylinder));;
	return (objects);
}

t_objects	*rt_objlast(t_objects *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
