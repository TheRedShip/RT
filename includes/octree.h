/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:58:12 by marvin            #+#    #+#             */
/*   Updated: 2024/04/27 15:58:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# include "minirt.h"

typedef struct	s_boundary
{
	t_vec3f		origin;
	t_vec3f		size;
}				t_boundary;

typedef struct	s_octree
{
	int				is_divided;
	t_boundary		boundary;
	t_objects		*objects;
	struct s_octree	*children[8];
}				t_octree;

t_boundary	get_boundary(t_objects *object);
void		create_octree(t_scene *scene);

#endif