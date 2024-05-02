/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:40:57 by ycontre           #+#    #+#             */
/*   Updated: 2024/05/02 19:25:16 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bvh	*create_bvh_node(t_vec3f origin, t_vec3f size)
{
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

	return (x1 < x4 && x2 > x3 &&
		y1 < y4 && y2 > y3 &&
		z1 < z4 && z2 > z3);
}

void		create_sphere(t_scene *scene, t_vec3f origin, t_vec3f color)
{
	t_objects *objects = rt_add_objects(&scene, "sp");
	objects->origin = origin;
	objects->sphere->diameter = 0.2;
	objects->material.emission_power = 2;
	objects->material.color = color;
}
void		show_boundary(t_scene *scene, t_boundary boundary, t_vec3f color)
{
	create_sphere(scene, boundary.origin, color);
	create_sphere(scene, vec3f_add_v(boundary.origin, (t_vec3f){boundary.size.x, 0, 0}), color);
	create_sphere(scene, vec3f_add_v(boundary.origin, (t_vec3f){0, boundary.size.y, 0}), color);
	create_sphere(scene, vec3f_add_v(boundary.origin, (t_vec3f){0, 0, boundary.size.z}), color);
	create_sphere(scene, vec3f_add_v(boundary.origin, (t_vec3f){boundary.size.x, boundary.size.y, 0}), color);
	create_sphere(scene, vec3f_add_v(boundary.origin, (t_vec3f){0, boundary.size.y, boundary.size.z}), color);
	create_sphere(scene, vec3f_add_v(boundary.origin, (t_vec3f){boundary.size.x, 0, boundary.size.z}), color);
	create_sphere(scene, vec3f_add_v(boundary.origin, (t_vec3f){boundary.size.x, boundary.size.y, boundary.size.z}), color);
}
void	show_boundary_objects(t_scene *scene)
{
	t_objects *obj;

	obj = scene->objects;
	while (obj)
	{
		if (obj->material.emission_power == 2.0f || !obj->sphere)
		{
			obj = obj->next;
			continue;
		}
		show_boundary(scene, get_boundary(obj), (t_vec3f){1, 1, 1});
		obj = obj->next;
	}
}
void		show_bvh(t_scene *scene, t_bvh *bvh, t_vec3f color)
{
	if (bvh->leaf)
		show_boundary(scene, bvh->boundary, color);
	if (bvh->divided)
	{
		for(int i = 0; i < 2; i++)
			show_bvh(scene, bvh->children[i], vec3f_mul_v(color, (t_vec3f){0.7, 0.4, 0.3}));
	}
}

void		sub_divide(t_bvh *bvh, int depth)
{
	t_vec3f	origin;;
	t_vec3f half;
	int		dim;

	origin = bvh->boundary.origin;
	dim = depth % 3;
	if (dim == 0 || 1)
	{
		half = (t_vec3f){bvh->boundary.size.x, bvh->boundary.size.y / 2.0f, bvh->boundary.size.z};
		bvh->children[1] = create_bvh_node(vec3f_add_v(origin, (t_vec3f){0, half.y, 0}), half);
	}
	else if (dim == 1)
	{
		half = (t_vec3f){bvh->boundary.size.x / 2.0f, bvh->boundary.size.y, bvh->boundary.size.z};
		bvh->children[1] = create_bvh_node(vec3f_add_v(origin, (t_vec3f){half.x, 0, 0}), half);
	}
	else
	{
		half = (t_vec3f){bvh->boundary.size.x, bvh->boundary.size.y, bvh->boundary.size.z / 2.0f};
		bvh->children[1] = create_bvh_node(vec3f_add_v(origin, (t_vec3f){0, 0, half.z}), half);
	}
	bvh->children[0] = create_bvh_node(origin, half);
}

void	insert_bvh(t_bvh *bvh, t_objects *object, int depth)
{
	if (!boundary_intersect(bvh->boundary, object))
		return ;
	if (depth > 0 && bvh->obj_count < MAX_OBJECTS)
	{
		bvh->obj_count++;
		return ;
	}
	if (!bvh->divided)
	{
		sub_divide(bvh, depth);
		bvh->divided = 1;
	}
	for (int i = 0; i < 2; i++)
		insert_bvh(bvh->children[i], object, depth + 1);
	return ;
}

void	insert_obj_bvh(t_bvh *bvh, t_objects *object, int depth)
{
	if (!boundary_intersect(bvh->boundary, object))
		return ;
	if (!bvh->divided)
	{
		bvh->objects[bvh->obj_count - 1] = object;
		bvh->obj_count--;
		bvh->leaf = 1;
		printf("size %f %f %f\n", bvh->boundary.size.x, bvh->boundary.size.y, bvh->boundary.size.z);
		return ;
	}
	for (int i = 0; i < 2; i++)
		insert_obj_bvh(bvh->children[i], object, depth + 1);
	return ;
}


void		create_bvh(t_scene *scene)
{
	t_bvh	*bvh;

	bvh = ft_calloc(1, sizeof(t_bvh));
	if (!bvh)
		rt_free_scene(scene);
	bvh->boundary.origin = (t_vec3f){-10, -10, -10};
	bvh->boundary.size = (t_vec3f){20, 20, 20};

	t_objects *obj = scene->objects;
	while (obj)
	{
		if (obj->type == OBJ_SPHER)
			insert_bvh(bvh, obj, 0);
		obj = obj->next;
	}
	obj = scene->objects;
	while (obj)
	{
		if (obj->type == OBJ_SPHER)
			insert_obj_bvh(bvh, obj, 0);
		obj = obj->next;
	}
	scene->bvh = bvh;

	// show_boundary_objects(scene);
	// t_ray ray = (t_ray){(t_vec3f){0, 0, 0},(t_vec3f){0, 1, 0}};
	// t_hitInfo hit_info = bvh_trace_ray_bis(scene, scene->bvh, ray);
	// printf("hit distance: %f\n", hit_info.distance);
	// printf("%p\n", hit_info.obj->sphere);
	// create_sphere(scene, hit_info.position, (t_vec3f){1, 0, 0});

	// create_sphere(scene, ray.origin, (t_vec3f){1, 0, 0});
	// for(int i = 0; i < 5; i++)
		// create_sphere(scene, vec3f_add_v(ray.origin, vec3f_mul_f(vec3f_mul_f(ray.direction, i), 0.2)), (t_vec3f){1, 0.5, 0});

	show_bvh(scene, scene->bvh, (t_vec3f){1,1,1});
}
