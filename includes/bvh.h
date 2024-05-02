/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:22:59 by ycontre           #+#    #+#             */
/*   Updated: 2024/05/02 19:16:37 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "minirt.h"

# define MAX_OBJECTS 4

typedef struct	s_boundary
{
	t_vec3f		origin;
	t_vec3f		size;
}				t_boundary;

typedef struct	s_bvh
{
	int				leaf;
	int				divided;
	int				obj_count;
	t_boundary		boundary;
	struct s_bvh	*children[2];
	t_objects		*objects[MAX_OBJECTS];
}				t_bvh;

t_boundary	get_boundary(t_objects *object);
void		create_bvh(t_scene *scene);

#endif