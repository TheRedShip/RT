/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:33:00 by marvin            #+#    #+#             */
/*   Updated: 2024/04/13 22:33:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	get_texture_color(t_hitInfo hit_info, int is_specular)
{
	int			color_hex;
	t_vec3f		color;
	t_vec2f		uv;
	t_vec3f		outward_normal;

	uv.x = 0.0f;
	uv.y = 0.0f;
	color = (t_vec3f){1.0f, 1.0f, 1.0f};
	if (hit_info.obj->type == OBJ_SPHER)
	{
		outward_normal = vec3f_div_f(vec3f_sub_v(hit_info.position, hit_info.obj->origin), (hit_info.obj->sphere->diameter / 2));
		uv.x = 1 - (0.5 + atan2(outward_normal.z, outward_normal.x) / (2 * M_PI));
		uv.y = 1 - (0.5 + asin(outward_normal.y) / M_PI);
	}
	else if (hit_info.obj->type == OBJ_PLANE)
	{
		uv.x = hit_info.position.x - floor(hit_info.position.x);
		uv.y = hit_info.position.z - floor(hit_info.position.z);
	}
	else if (hit_info.obj->type == OBJ_QUADS)
	{
		t_vec3f A = vec3f_add_v(hit_info.obj->origin, hit_info.obj->quad->up_corner);
		//t_vec3f C = vec3f_add_v(hit_info.obj->origin, hit_info.obj->quad->right_corner);
		t_vec3f B = vec3f_add_v(A, hit_info.obj->quad->right_corner);
		t_vec3f D = hit_info.obj->origin;
		
		t_vec3f AB = vec3f_sub_v(B, A);
		t_vec3f AD = vec3f_sub_v(D, A);

		t_vec3f AP = vec3f_sub_v(hit_info.position, A);
		float AB_dot_AP = vec3f_dot(AB, AP);
		float AB_dot_AB = vec3f_dot(AB, AB);
		float AD_dot_AP = vec3f_dot(AD, AP);
		float AD_dot_AD = vec3f_dot(AD, AD);
		
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

t_vec3f	get_checkered_color(t_hitInfo hit_info)
{
	if (hit_info.obj->type == OBJ_SPHER)
	{
		if (((int)(floor(0.25 * (hit_info.normal.x + 0.001)) + \
		floor(0.25 * (hit_info.normal.y + 0.001)) + \
		floor(0.25 * (hit_info.normal.z + 0.001)))) % 2 == 0)
			return (t_vec3f){0.1, 0.1, 0.1};
	}
	else if (hit_info.obj->type == OBJ_PLANE)
	{
		if (((int)(floor(0.25 * (hit_info.position.x + 0.001)) + \
		floor(0.25 * (hit_info.position.y + 0.001)) + \
		floor(0.25 * (hit_info.position.z + 0.001)))) % 2 == 0)
			return (t_vec3f){0.1, 0.1, 0.1};
	}
	return (t_vec3f){1.0, 1.0, 1.0};
}

void	calcul_color(t_vec3f *contribution, t_hitInfo hit_info, int is_specular)
{
	*contribution = vec3f_mul_v(*contribution, lerp(hit_info.obj->material.color, (t_vec3f){1.0f, 1.0f, 1.0f}, is_specular));
	if (hit_info.obj->material.checkered == 1)
		*contribution = vec3f_mul_v(*contribution, get_checkered_color(hit_info));
	if (hit_info.obj->material.texture.exist == 1)
		*contribution = vec3f_mul_v(*contribution, get_texture_color(hit_info, is_specular));
}

void	calcul_light(t_hitInfo hit_info, t_scene *scene, t_vec3f *light, t_vec3f *contribution, int is_specular)
{
	t_vec3f		light_direction;
	float		diffuse_ratio;

	light_direction = normalize(vec3f_sub_v(hit_info.position, scene->lights->origin));
	diffuse_ratio = vec3f_dot(hit_info.normal, vec3f_mul_f(light_direction, -1.0f));
	if (diffuse_ratio < 0.0f)
		diffuse_ratio = 0.0f;
	if (scene->lights->hard == 1 && scene->lights->ratio > 0.0f)
	{
		t_hitInfo	shadow_hit_info;
		t_ray		ray;
		ray.origin = vec3f_add_v(hit_info.position, vec3f_mul_f(hit_info.normal, 0.0001f));
		ray.direction = vec3f_mul_f(light_direction, -1.0f);
		shadow_hit_info = trace_ray(scene, scene->octree, ray);
		if (shadow_hit_info.distance > 0.0f && shadow_hit_info.distance < vec3f_length(vec3f_sub_v(scene->lights->origin, hit_info.position)))
			diffuse_ratio = 0.0f;
	}
	*light = vec3f_add_v(*light, vec3f_mul_f(scene->lights->color, diffuse_ratio * scene->lights->ratio));
	*light = vec3f_add_v(*light, vec3f_mul_f(hit_info.obj->material.color, hit_info.obj->material.emission_power));
	calcul_color(contribution, hit_info, is_specular);
}