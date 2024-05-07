/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:18:56 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 23:18:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "minirt.h"

# define MAX_OBJECTS 10

typedef struct	s_ray	t_ray;

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

int			boxIntersection(t_ray ray, t_vec3f origin, t_vec3f rad);
void		create_bvh(t_scene *scene);
t_boundary	get_boundary(t_objects *object);

#endif