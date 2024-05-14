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

t_vec3f	get_checkered_color(t_hit_info h)
{
	t_vec2f		uv;

	uv = (t_vec2f){0.0f, 0.0f};
	if (h.obj->type == OBJ_PLANE)
	{
		if (((int)(floor(0.25 * (h.position.x + 0.001)) + \
		floor(0.25 * (h.position.y + 0.001)) + \
		floor(0.25 * (h.position.z + 0.001)))) % 2 == 0)
			return ((t_vec3f){0.1, 0.1, 0.1});
		return ((t_vec3f){1.0, 1.0, 1.0});
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

void	calcul_color(t_vec3f *color, t_hit_info hit, int is_spec)
{
	*color = v_mul_v(*color, \
		lerp(hit.obj->material.color, (t_vec3f){1.0f, 1.0f, 1.0f}, is_spec));
	if (hit.obj->material.checkered == 1)
		*color = v_mul_v(*color, get_checkered_color(hit));
	if (hit.obj->material.texture.exist == 1)
		*color = v_mul_v(*color, get_texture_color(hit, is_spec));
}

void	calcul_spots_lights(t_scene *s, float *dr, t_hit_info h, t_vec3f *l_c[2])
{
	t_ray		shadow_ray;
	t_hit_info	shadow_h;
	t_vec3f		l_direction;

	if (s->lights->ratio > 0.0f)
	{
		l_direction = normalize(v_sub_v(s->lights->origin, h.position));
		shadow_ray.origin = v_add_v(h.position, v_mul_f(h.normal, 0.0001f));
		shadow_ray.direction = l_direction;
		shadow_h = trace_ray(s, shadow_ray);
		if (!(shadow_h.distance > 0.0f && shadow_h.distance < \
				v_length(v_sub_v(s->lights->origin, h.position))))
			*dr = fmax(0.0f, v_dot(h.normal, l_direction));
		t_vec3f reflection_direction = reflect(l_direction, h.normal);
		float specular_term = pow(fmax(0.0f, v_dot(reflection_direction, normalize(v_sub_v(h.position, s->camera->origin)))), 5);//h.obj->material.specular_exponent);
		t_vec3f specular_color = v_mul_f(s->lights->color, specular_term * s->lights->ratio * *dr);
		*l_c[1] = v_add_v(*l_c[1], specular_color);
	}
}

void	calcul_light(t_hit_info hit, t_scene *scene, t_vec3f *l_c[2], int is_specular)
{
	float		dr;

	dr = 0.0f;
	calcul_spots_lights(scene, &dr, hit, l_c);
	if (dr > 0.0f && scene->lights->ratio > 0.0f)
		*l_c[0] = v_add_v(*l_c[0], \
				v_mul_f(scene->lights->color, dr * scene->lights->ratio));
	if (hit.obj->material.emission_power > 0.0f)
		*l_c[0] = v_add_v(*l_c[0], \
				v_mul_f(hit.obj->material.color, hit.obj->material.emission_power));
	calcul_color(l_c[1], hit, is_specular);
}
