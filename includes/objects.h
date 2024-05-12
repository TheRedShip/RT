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
	OBJ_SPHER		= 0,
	OBJ_PLANE		= 1,
	OBJ_CYLIN		= 2,
	OBJ_QUADS		= 3,
	OBJ_ELLIP		= 4,
	OBJ_PORTA		= 5,
	OBJ_TRIAN		= 6
}	t_obj_type;

typedef enum e_mat_type
{
	MAT_LAMBERT		= 0,
	MAT_DIELECTRIC	= 1
}	t_mat_type;

typedef struct s_hit_info	t_hit_info;
typedef struct s_ray		t_ray;

void		link_portals(t_scene *scene);

t_material	init_material(void);
t_texture	init_texture(t_scene *scene, char *path);
t_hit_info	hit_objects(t_ray ray, t_objects *obj);

t_vec3f		get_texture_color(t_hit_info hit_info, int is_specular);

void		rt_lstobj_addback(t_objects **lst, t_objects *new);
t_objects	*rt_add_objects(t_scene *scene, char *type);
void		rt_add_objlst(t_scene *scene, t_objects *objects);

#endif