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

t_vec3f	v_rotate_xy(t_vec3f v, float angle, int xy)
{
	float			rm[3][3];
	t_vec3f			result;

	if (xy == 0)
		apply_rotation_matrix_x(angle, rm);
	else
		apply_rotation_matrix_y(angle, rm);
	result.x = rm[0][0] * v.x + rm[0][1] * v.y + rm[0][2] * v.z;
	result.y = rm[1][0] * v.x + rm[1][1] * v.y + rm[1][2] * v.z;
	result.z = rm[2][0] * v.x + rm[2][1] * v.y + rm[2][2] * v.z;
	return (result);
}

t_vec2f	get_sphere_texture(t_hit_info hit_info)
{
	t_vec3f		o_n;
	t_vec2f		uv;

	o_n = v_div_f(\
				v_sub_v(hit_info.position, hit_info.obj->origin), \
				(hit_info.obj->sphere->diameter / 2));
	o_n = v_rotate_xy(o_n, hit_info.obj->sphere->rotation.x, 1);
	o_n = v_rotate_xy(o_n, hit_info.obj->sphere->rotation.y, 0);
	uv.x = 1 - (0.5 + atan2(o_n.z, o_n.x) / (2 * M_PI));
	uv.y = 1 - (0.5 + asin(o_n.y) / M_PI);
	return (uv);
}

t_vec2f	get_quad_texture(t_hit_info hit_info)
{
	t_vec3f		abd[3];
	t_vec3f		ab_ad_ap[3];
	float		dot[4];
	t_vec2f		uv;

	abd[0] = v_add_v(hit_info.obj->origin, hit_info.obj->quad->up_corner);
	abd[1] = v_add_v(abd[0], hit_info.obj->quad->right_corner);
	abd[2] = hit_info.obj->origin;
	ab_ad_ap[0] = v_sub_v(abd[1], abd[0]);
	ab_ad_ap[1] = v_sub_v(abd[2], abd[0]);
	ab_ad_ap[2] = v_sub_v(hit_info.position, abd[0]);
	dot[0] = v_dot(ab_ad_ap[0], ab_ad_ap[2]);
	dot[1] = v_dot(ab_ad_ap[0], ab_ad_ap[0]);
	dot[2] = v_dot(ab_ad_ap[1], ab_ad_ap[2]);
	dot[3] = v_dot(ab_ad_ap[1], ab_ad_ap[1]);
	uv.y = 1 - (dot[0] / dot[1]);
	uv.x = 1 - (dot[2] / dot[3]);
	return (uv);
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
		uv = get_sphere_texture(hit_info);
	else if (hit_info.obj->type == OBJ_PLANE)
	{
		uv.x = hit_info.position.x - floor(hit_info.position.x);
		uv.y = hit_info.position.z - floor(hit_info.position.z);
	}
	else if (hit_info.obj->type == OBJ_QUADS)
		uv = get_quad_texture(hit_info);
	color_hex = get_pixel(&hit_info.obj->material.texture.data, \
						uv.x * (hit_info.obj->material.texture.width - 1), \
						uv.y * (hit_info.obj->material.texture.height - 1));
	color = hex_to_rgb(color_hex);
	color = lerp(color, (t_vec3f){1.0f, 1.0f, 1.0f}, is_specular);
	return (color);
}
