/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:00:55 by marvin            #+#    #+#             */
/*   Updated: 2024/03/31 00:00:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

typedef struct	s_hitInfo
{
	float		distance;
	t_vec3f		position;
	t_vec3f		normal;
	t_objects	*obj;
}	t_hitInfo;

typedef struct	s_ray
{
	t_vec3f	origin;
	t_vec3f	direction;
}	t_ray;

int			rgb_to_hex(t_vec3f rgb);
int			rt_render_scene(t_scene *scene);
t_vec3f		calculate_ray_direction(t_scene *scene, t_vec3f prev);

#endif