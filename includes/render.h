/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:00:55 by marvin            #+#    #+#             */
/*   Updated: 2024/04/30 19:57:05 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

typedef struct s_hit_info
{
	float		distance;
	t_vec3f		position;
	t_vec3f		normal;
	t_objects	*obj;
}	t_hit_info;

typedef struct s_ray
{
	t_vec3f	origin;
	t_vec3f	direction;
}	t_ray;

t_vec3f		calculate_ray_direction(t_scene *scene, t_vec3f prev);
void		calcul_light(t_hit_info h, t_scene *s, \
						t_vec3f *l_c[2], int is_specular);
t_hit_info	trace_ray(t_scene *scene, t_ray ray);

t_hit_info	portal_ray(t_scene *scene, t_hit_info hit, t_ray ray);
t_ray		new_ray(t_hit_info hit_info, t_ray ray, \
			t_threads *thread, int *is_specular);

int			rt_render_scene(t_scene *scene);
void		rt_render_image(t_scene *scene, t_vec3f **image);

int			rgb_to_hex(t_vec3f rgb);
t_vec3f		hex_to_rgb(int hex);

t_vec2f		get_uv(t_threads *thread, float x, float y);

#endif
