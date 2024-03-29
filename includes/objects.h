/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:24:09 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 17:24:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

typedef enum e_obj_type
{
	OBJ_SPHER = 0,
	OBJ_PLANE = 1,
	OBJ_CYLIN = 2
}	t_obj_type;

t_objects	*rt_add_objects(t_scene **scene, char *type);
t_objects	*rt_objlast(t_objects *lst);

#endif