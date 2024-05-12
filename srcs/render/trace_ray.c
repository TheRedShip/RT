/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:12:08 by marvin            #+#    #+#             */
/*   Updated: 2024/05/12 17:12:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_info	basic_trace_ray(t_scene *scene, t_ray ray)
{
	t_hit_info	temp_hit;
	t_objects	*temp_object;
	t_hit_info	closest_hit;

	temp_object = scene->objects;
	closest_hit.distance = -1.0f;
	while (temp_object)
	{
		temp_hit = hit_objects(ray, temp_object);
		if (temp_hit.distance > 0.0f
			&& (temp_hit.distance < closest_hit.distance
				|| closest_hit.distance < 0.0f))
		{
			closest_hit = temp_hit;
			closest_hit.obj = temp_object;
		}
		temp_object = temp_object->next;
	}
	if (closest_hit.distance > 0.0f && closest_hit.obj->type == OBJ_PORTA)
		return (portal_ray(scene, closest_hit, ray));
	return (closest_hit);
}

t_hit_info	closest_hit_in_bvh(t_bvh *bvh, t_ray ray)
{
	t_hit_info	h;
	t_hit_info	tmp;
	t_list		*obj;

	h.distance = -1.0f;
	obj = bvh->objects;
	while (obj)
	{
		tmp = hit_objects(ray, (t_objects *)obj->content);
		if (tmp.distance >= 0 && (tmp.distance < h.distance || h.distance < 0))
		{
			h = tmp;
			h.obj = (t_objects *)obj->content;
		}
		obj = obj->next;
	}
	return (h);
}

t_hit_info	bvh_trace_ray(t_bvh *bvh, t_ray ray)
{
	t_hit_info	hit_info;
	t_hit_info	hit_0;
	t_hit_info	hit_1;

	hit_info.distance = -1.0f;
	if (!box_intersection(ray, bvh->boundary.origin, bvh->boundary.size))
		return (hit_info);
	if (bvh->leaf)
		return (closest_hit_in_bvh(bvh, ray));
	if (bvh->divided)
	{
		hit_0 = bvh_trace_ray(bvh->children[0], ray);
		hit_1 = bvh_trace_ray(bvh->children[1], ray);
		if (hit_0.distance >= 0.0f && \
				(hit_1.distance < 0.0f || hit_0.distance <= hit_1.distance))
			return (hit_0);
		if (hit_1.distance >= 0.0f && \
				(hit_0.distance < 0.0f || hit_1.distance < hit_0.distance))
			return (hit_1);
	}
	return (hit_info);
}

t_hit_info	trace_ray(t_scene *scene, t_ray ray)
{
	if (scene->kdtree->is_bvh)
		return (bvh_trace_ray(scene->bvh, ray));
	return (basic_trace_ray(scene, ray));
}
