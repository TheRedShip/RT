/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:21:03 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 23:21:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bvh	*create_bvh_node(t_vec3f origin, t_vec3f size)
{
	static int id = 0;
	id++;
	printf("create bvh node %d\n", id);
	t_bvh	*bvh;

	bvh = ft_calloc(1, sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->leaf = 0;
	bvh->boundary.origin = origin;
	bvh->boundary.size = size;
	return (bvh);
}

int			boundary_intersect(t_boundary boundary, t_objects *object)
{
	t_boundary obj_boundary;

	obj_boundary = get_boundary(object);
	float x1 = boundary.origin.x;
	float y1 = boundary.origin.y;
	float z1 = boundary.origin.z;

	float x2 = boundary.origin.x + boundary.size.x;
	float y2 = boundary.origin.y + boundary.size.y;
	float z2 = boundary.origin.z + boundary.size.z;

	float x3 = obj_boundary.origin.x;
	float y3 = obj_boundary.origin.y;
	float z3 = obj_boundary.origin.z;

	float x4 = obj_boundary.origin.x + obj_boundary.size.x;
	float y4 = obj_boundary.origin.y + obj_boundary.size.y;
	float z4 = obj_boundary.origin.z + obj_boundary.size.z;

	return (x1 <= x4 && x2 >= x3 &&
		y1 <= y4 && y2 >= y3 &&
		z1 <= z4 && z2 >= z3);
}

void		create_sphere(t_scene *scene, t_vec3f origin, t_vec3f color)
{
	t_objects *objects = rt_add_objects(scene, "sp");
	objects->origin = origin;
	objects->sphere->diameter = 0.2;
	objects->material.emission_power = 2;
	objects->material.color = color;
}
void		show_boundary(t_scene *scene, t_boundary boundary, t_vec3f color)
{
	create_sphere(scene, boundary.origin, color);
	create_sphere(scene, v_add_v(boundary.origin, (t_vec3f){boundary.size.x, 0, 0}), color);
	create_sphere(scene, v_add_v(boundary.origin, (t_vec3f){0, boundary.size.y, 0}), color);
	create_sphere(scene, v_add_v(boundary.origin, (t_vec3f){0, 0, boundary.size.z}), color);
	create_sphere(scene, v_add_v(boundary.origin, (t_vec3f){boundary.size.x, boundary.size.y, 0}), color);
	create_sphere(scene, v_add_v(boundary.origin, (t_vec3f){0, boundary.size.y, boundary.size.z}), color);
	create_sphere(scene, v_add_v(boundary.origin, (t_vec3f){boundary.size.x, 0, boundary.size.z}), color);
	create_sphere(scene, v_add_v(boundary.origin, (t_vec3f){boundary.size.x, boundary.size.y, boundary.size.z}), color);
}
void	show_boundary_objects(t_scene *scene)
{
	t_objects *obj;

	obj = scene->objects;
	while (obj)
	{
		if (obj->material.emission_power != 2.0f)
			show_boundary(scene, get_boundary(obj), (t_vec3f){0.2, 0.5, 0.2});
		obj = obj->next;
	}
}
void		show_bvh(t_scene *scene, t_bvh *bvh, t_vec3f color)
{
	// if (bvh->leaf)
		show_boundary(scene, bvh->boundary, color);
	if (bvh->divided)
	{
		for(int i = 0; i < 2; i++)
			show_bvh(scene, bvh->children[i], v_mul_v(color, (t_vec3f){0.8, 0.5, 0.4}));
	}
}

void		sub_divide(t_bvh *bvh, int depth)
{
	t_vec3f	origin;
	t_vec3f half;
	int		dim;

	origin = bvh->boundary.origin;
	dim = depth % 3;
	if (dim == 0)
	{
		half = (t_vec3f){bvh->boundary.size.x, bvh->boundary.size.y / 2.0f, bvh->boundary.size.z};
		bvh->children[1] = create_bvh_node(v_add_v(origin, (t_vec3f){0, half.y, 0}), half);
	}
	else if (dim == 1)
	{
		half = (t_vec3f){bvh->boundary.size.x / 2.0f, bvh->boundary.size.y, bvh->boundary.size.z};
		bvh->children[1] = create_bvh_node(v_add_v(origin, (t_vec3f){half.x, 0, 0}), half);
	}
	else
	{
		half = (t_vec3f){bvh->boundary.size.x, bvh->boundary.size.y, bvh->boundary.size.z / 2.0f};
		bvh->children[1] = create_bvh_node(v_add_v(origin, (t_vec3f){0, 0, half.z}), half);
	}
	bvh->children[0] = create_bvh_node(origin, half);
}

int	insert_bvh(t_bvh *bvh, t_objects *object, int depth)
{
	if (!boundary_intersect(bvh->boundary, object))
		return (0);
	if (depth > 0 && bvh->obj_count < MAX_OBJECTS)
	{
		bvh->leaf = 1;
		bvh->objects[bvh->obj_count] = object;
		bvh->obj_count++;
		return (1);
	}
	if (!bvh->divided)
	{
		sub_divide(bvh, depth);
		bvh->divided = 1;
	}
	if (bvh->obj_count == MAX_OBJECTS && bvh->leaf)
	{
		bvh->leaf = 0;
		for (int i = 0; i < MAX_OBJECTS; i++)
		{
			for (int j = 0; j < 2; j++)
				if(insert_bvh(bvh->children[j], bvh->objects[i], depth + 1))
					break;
		}
	}
	insert_bvh(bvh->children[0], object, depth + 1);
	insert_bvh(bvh->children[1], object, depth + 1);
	return (1);
}

t_hit_info	closest_hit_in_bvh_bis(t_bvh *bvh, t_ray ray)
{
	int			i;
	t_hit_info	hit_info;
	t_hit_info	tmp_hit;

	hit_info.distance = -1.0f;
	i = 0;
	while (i < bvh->obj_count)
	{
		tmp_hit = hit_objects(ray, bvh->objects[i]);
		if (tmp_hit.distance >= 0 && (tmp_hit.distance < hit_info.distance || hit_info.distance < 0))
		{
			hit_info = tmp_hit;
			hit_info.obj = bvh->objects[i];
		}
		i++;
	}
	return (hit_info);
}

t_hit_info	bvh_trace_ray_bis(t_bvh *bvh, t_ray ray)
{
	t_hit_info	hit_info;
	t_hit_info	hit_0;
	t_hit_info	hit_1;

	hit_info.distance = -1.0f;
	if (!boxIntersection(ray, bvh->boundary.origin, bvh->boundary.size))
		return (hit_info);
	if (bvh->leaf)
		return (closest_hit_in_bvh_bis(bvh, ray));
	if (bvh->divided)
	{
		hit_0 = bvh_trace_ray_bis(bvh->children[0], ray);
		hit_1 = bvh_trace_ray_bis(bvh->children[1], ray);
		if (hit_0.distance >= 0.0f && (hit_1.distance < 0.0f || hit_0.distance <= hit_1.distance))
			return (hit_0);
		if (hit_1.distance >= 0.0f && (hit_0.distance < 0.0f || hit_1.distance < hit_0.distance))
			return (hit_1);
	}
	return (hit_info);
}

void		create_bvh(t_scene *scene)
{
	t_bvh	*bvh;

	bvh = ft_calloc(1, sizeof(t_bvh));
	if (!bvh)
		rt_free_scene(scene, 1);
	bvh->boundary.origin = (t_vec3f){-100, -100, -100};
	bvh->boundary.size = (t_vec3f){200, 200, 200};

	t_objects *obj = scene->objects;
	while (obj)
	{
		if (obj->type != OBJ_PLANE)
			insert_bvh(bvh, obj, 0);
		obj = obj->next;
	}
	scene->bvh = bvh;

	// show_boundary_objects(scene);
	// t_ray ray = (t_ray){(t_vec3f){-0.5, -3, 2},(t_vec3f){0, 3, -1}};
	// t_hit_info hit_info = bvh_trace_ray_bis(scene->bvh, ray);
	// printf("hit distance: %f\n", hit_info.distance);
	// if (hit_info.distance >= 0)
	// {
	// 	hit_info.obj->material.color = (t_vec3f){1, 0.2, 0.2};
	// 	create_sphere(scene, hit_info.position, (t_vec3f){1, 0, 0});
	// }
	// create_sphere(scene, ray.origin, (t_vec3f){1, 0, 0});
	// for(int i = 0; i < 5; i++)
	// 	create_sphere(scene, v_add_v(ray.origin, v_mul_f(v_mul_f(ray.direction, i), 0.2)), (t_vec3f){1, 0.5, 0});

	// show_bvh(scene, scene->bvh, (t_vec3f){1,1,1});
}