/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:00:33 by marvin            #+#    #+#             */
/*   Updated: 2024/05/12 18:00:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	get_bump_normal(t_hit_info hit_info, t_texture bump)
{
	int			color_hex;
	t_vec2f		uv;
	t_vec3f		bump_normal;

	uv.x = 0.0f;
	uv.y = 0.0f;
	if (hit_info.obj->type == OBJ_SPHER)
		uv = get_sphere_uv(hit_info);
	else if (hit_info.obj->type == OBJ_PLANE)
		uv = get_plane_uv(hit_info);
	else if (hit_info.obj->type == OBJ_QUADS)
		uv = get_quad_uv(hit_info);
	color_hex = get_pixel(&bump.data, \
			uv.x * (bump.width - 1), uv.y * (bump.height - 1));
	// return (hit_info.normal);
	
	bump_normal = hex_to_rgb(color_hex);
	bump_normal = v_add_f(v_mul_f(bump_normal, 2.0f), -1.0f);
	bump_normal = normalize(bump_normal);
	bump_normal = v_mul_v(hit_info.normal, bump_normal);
	return (bump_normal);
}

t_vec3f	get_texture_color(t_hit_info hit_info, int is_specular)
{
	int			color_hex;
	t_vec3f		color;
	t_vec2f		uv;

	uv.x = 0.0f;
	uv.y = 0.0f;
	color = (t_vec3f){1.0f, 1.0f, 1.0f};
	if (hit_info.obj->type == OBJ_SPHER)
		uv = get_sphere_uv(hit_info);
	else if (hit_info.obj->type == OBJ_PLANE)
		uv = get_plane_uv(hit_info);
	else if (hit_info.obj->type == OBJ_QUADS)
		uv = get_quad_uv(hit_info);
	color_hex = get_pixel(&hit_info.obj->material.texture.data, \
						uv.x * (hit_info.obj->material.texture.width - 1), \
						uv.y * (hit_info.obj->material.texture.height - 1));
	color = hex_to_rgb(color_hex);
	color = lerp(color, (t_vec3f){1.0f, 1.0f, 1.0f}, is_specular);
	return (color);
}
