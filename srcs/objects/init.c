/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:23:35 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 17:23:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objects	*rt_add_objects(t_scene **scene, char *type)
{
	t_objects *objects;

	if (!(*scene)->objects)
	{
		(*scene)->objects = ft_calloc(1, sizeof(t_objects));
		objects = (*scene)->objects;
	}
	else
	{
		objects = (*scene)->objects;
		while (objects->next)
			objects = objects->next;
		objects->next = ft_calloc(1, sizeof(t_objects));
		objects = objects->next;
	}
	if (!objects)
		rt_free_scene(*scene);
	if (ft_strncmp(type, "sp", 2) == 0)
	{
		objects->type = OBJ_SPHER;
		objects->sphere = ft_calloc(1, sizeof(t_sphere));
	}
	else if (ft_strncmp(type, "pl", 2) == 0)
	{
		objects->type = OBJ_PLANE;
		objects->plane = ft_calloc(1, sizeof(t_plane));
	}
	else if (ft_strncmp(type, "cy", 2) == 0)
	{
		objects->type = OBJ_CYLIN;
		objects->cylinder = ft_calloc(1, sizeof(t_cylinder));;
	}
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