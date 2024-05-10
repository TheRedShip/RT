/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:33:00 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 13:26:58 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_rm(float rm[3][3], float s, float c, int xy)
{
	if (xy == 1)
	{
		rm[0][0] = c;
		rm[0][1] = 0;
		rm[0][2] = s;
		rm[1][0] = 0;
		rm[1][1] = 1;
		rm[1][2] = 0;
		rm[2][0] = -s;
		rm[2][1] = 0;
		rm[2][2] = c;
		return ;
	}
	rm[0][0] = 1;
	rm[0][1] = 0;
	rm[0][2] = 0;
	rm[1][0] = 0;
	rm[1][1] = c;
	rm[1][2] = -s;
	rm[2][0] = 0;
	rm[2][1] = s;
	rm[2][2] = c;
}

t_vec3f	v_rotate_xy(t_vec3f v, float angle, int xy)
{
	float			s;
	float			c;
	float			rm[3][3];
	t_vec3f			result;

	s = sin(angle);
	c = cos(angle);
	fill_rm(rm, s, c, xy);
	result.x = rm[0][0] * v.x + rm[0][1] * v.y + rm[0][2] * v.z;
	result.y = rm[1][0] * v.x + rm[1][1] * v.y + rm[1][2] * v.z;
	result.z = rm[2][0] * v.x + rm[2][1] * v.y + rm[2][2] * v.z;
	return (result);
}

t_vec3f	get_texture_color(t_hit_info hit_info, int is_specular)
{
	int			color_hex;
	t_vec2f		uv;
	t_vec3f		color;
	t_vec3f		o_n;

	uv.x = 0.0f;
	uv.y = 0.0f;
	color = (t_vec3f){1.0f, 1.0f, 1.0f};
	if (hit_info.obj->type == OBJ_SPHER)
	{
		o_n = v_div_f(\
					v_sub_v(hit_info.position, hit_info.obj->origin), \
					(hit_info.obj->sphere->diameter / 2));
		o_n = v_rotate_xy(o_n, hit_info.obj->sphere->rotation.x, 1);
		o_n = v_rotate_xy(o_n, hit_info.obj->sphere->rotation.y, 0);
		uv.x = 1 - (0.5 + atan2(o_n.z, o_n.x) / (2 * M_PI));
		uv.y = 1 - (0.5 + asin(o_n.y) / M_PI);
	}
	else if (hit_info.obj->type == OBJ_PLANE)
	{
		uv.x = hit_info.position.x - floor(hit_info.position.x);
		uv.y = hit_info.position.z - floor(hit_info.position.z);
	}
	else if (hit_info.obj->type == OBJ_QUADS)
	{
		t_vec3f A = v_add_v(hit_info.obj->origin, hit_info.obj->quad->up_corner);
		t_vec3f B = v_add_v(A, hit_info.obj->quad->right_corner);
		t_vec3f D = hit_info.obj->origin;
		
		t_vec3f AB = v_sub_v(B, A);
		t_vec3f AD = v_sub_v(D, A);

		t_vec3f AP = v_sub_v(hit_info.position, A);
		float AB_dot_AP = v_dot(AB, AP);
		float AB_dot_AB = v_dot(AB, AB);
		float AD_dot_AP = v_dot(AD, AP);
		float AD_dot_AD = v_dot(AD, AD);
		
		uv.y = 1 - (AB_dot_AP / AB_dot_AB);
		uv.x = 1 - (AD_dot_AP / AD_dot_AD);

		if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f)
			return (color);
	}
	color_hex = get_pixel(&hit_info.obj->material.texture.data, uv.x * (hit_info.obj->material.texture.width - 1), uv.y * (hit_info.obj->material.texture.height - 1));
	color = hex_to_rgb(color_hex);
	color = lerp(color, (t_vec3f){1.0f, 1.0f, 1.0f}, is_specular);
	return (color);
}

t_vec3f	get_checkered_color(t_hit_info h)
{
	t_vec2f		uv;

	uv = (t_vec2f){0.0f, 0.0f};
	if (h.obj->type == OBJ_PLANE)
	{
		if (((int)(floor(0.25 * (h.position.x + 0.001)) + \
		floor(0.25 * (h.position.y + 0.001)) + \
		floor(0.25 * (h.position.z + 0.001)))) % 2 == 0)
			return (t_vec3f){0.1, 0.1, 0.1};
		return (t_vec3f){1.0, 1.0, 1.0};
	}
	else if (h.obj->type == OBJ_SPHER)
	{
		uv.x = 1 - (atan2f(h.normal.x, h.normal.z) / (2 * M_PI) + 0.5);
		uv.y = 1 - acosf(h.normal.y / v_length(h.normal)) / M_PI;
	}
	else if (h.obj->type == OBJ_CYLIN)
	{
		uv.x = 1 - (atan2f(h.normal.x, h.normal.z) / (2 * M_PI) + 0.5);
		uv.y = (int)h.normal.y % 1;
	}
	if (((int)(floor(10 * (uv.x + 0.001)) + \
		floor(10 * (uv.y + 0.001)))) % 2 == 0)
		return ((t_vec3f){0.1, 0.1, 0.1});
	return ((t_vec3f){1.0, 1.0, 1.0});
}

void	calcul_color(t_vec3f *contribution, t_hit_info hit_info, int is_specular)
{
	*contribution = v_mul_v(*contribution, lerp(hit_info.obj->material.color, (t_vec3f){1.0f, 1.0f, 1.0f}, is_specular));
	if (hit_info.obj->material.checkered == 1)
		*contribution = v_mul_v(*contribution, get_checkered_color(hit_info));
	if (hit_info.obj->material.texture.exist == 1)
		*contribution = v_mul_v(*contribution, get_texture_color(hit_info, is_specular));
}

void	calcul_light(t_hit_info h, t_scene *s, t_vec3f *l, t_vec3f *contribution, int is_specular)
{
	t_hit_info	shadow_h;
	t_vec3f		l_direction;
	t_ray		ray;
	float		dr;

	dr = 0.0f;
	l_direction = normalize(v_sub_v(h.position, s->lights->origin));
	if (s->lights->ratio > 0.0f)
	{
		ray.origin = v_add_v(h.position, v_mul_f(h.normal, 0.0001f));
		ray.direction = v_mul_f(l_direction, -1.0f);
		shadow_h = trace_ray(s, ray);
		if (!(shadow_h.distance > 0.0f && shadow_h.distance < \
				v_length(v_sub_v(s->lights->origin, h.position))))
			dr = v_dot(h.normal, v_mul_f(l_direction, -1.0f));
		if (dr < 0.0f)
			dr = 0.0f;
	}
	if (dr > 0.0f && s->lights->ratio > 0.0f)
		*l = v_add_v(*l, v_mul_f(s->lights->color, dr * s->lights->ratio));
	if (h.obj->material.emission_power > 0.0f || h.obj->material.color.x > 1.0f
		|| h.obj->material.color.y > 1.0f || h.obj->material.color.z > 1.0f)
		*l = v_add_v(*l, v_mul_f(h.obj->material.color, \
				h.obj->material.emission_power));
	calcul_color(contribution, h, is_specular);
}
