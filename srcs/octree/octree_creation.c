/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:58:44 by marvin            #+#    #+#             */
/*   Updated: 2024/04/27 15:58:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_octree	*create_octree_node(t_vec3f origin, t_vec3f size)
{
	t_octree	*octree;

	octree = ft_calloc(1, sizeof(t_octree));
	if (!octree)
		return (NULL);
	octree->boundary.origin = origin;
	octree->boundary.size = size;
	return (octree);
}

int			boundary_contains(t_boundary boundary, t_objects *object)
{
	return (object->origin.x >= boundary.origin.x - boundary.size.x && \
			object->origin.x <= boundary.origin.x + boundary.size.x && \
			object->origin.y >= boundary.origin.y - boundary.size.y && \
			object->origin.y <= boundary.origin.y + boundary.size.y && \
			object->origin.z >= boundary.origin.z - boundary.size.z && \
			object->origin.z <= boundary.origin.z + boundary.size.z);
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

int			insert_octree(t_octree *octree, t_objects *object)
{
	if (!boundary_intersect(octree->boundary, object))
		return (0);
	if (octree->objects == NULL)
	{
		octree->objects = object;
		return (1);
	}
	if (!octree->is_divided)
	{
		t_vec3f half = vec3f_div_f(octree->boundary.size, 2);
		t_vec3f origin = octree->boundary.origin;
		octree->children[0] = create_octree_node(origin, half);
		octree->children[1] = create_octree_node(vec3f_add_v(origin, (t_vec3f){half.x, 0, 0}), half);
		octree->children[2] = create_octree_node(vec3f_add_v(origin, (t_vec3f){0, half.y, 0}), half);
		octree->children[3] = create_octree_node(vec3f_add_v(origin, (t_vec3f){0, 0, half.z}), half);
		octree->children[4] = create_octree_node(vec3f_add_v(origin, (t_vec3f){half.x, half.y, 0}), half);
		octree->children[5] = create_octree_node(vec3f_add_v(origin, (t_vec3f){0, half.y, half.z}), half);
		octree->children[6] = create_octree_node(vec3f_add_v(origin, (t_vec3f){half.x, 0, half.z}), half);
		octree->children[7] = create_octree_node(vec3f_add_v(origin, half), half);
		octree->is_divided = 1;
	}
	for (int i = 0; i < 8; i++)
		insert_octree(octree->children[i], object);
	return (1);
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
void		show_octree(t_scene *scene, t_octree *octree, t_vec3f color, int is_recursive)
{
	
	if (octree->objects)
		show_boundary(scene, octree->boundary, color);
	if (octree->is_divided && is_recursive)
	{
		for(int i = 0; i < 8; i++)
			show_octree(scene, octree->children[i], vec3f_mul_v(color, (t_vec3f){0.7, 0.4, 0.3}), 1);
	}
}
void	show_boundary_objects(t_scene *scene)
{
	t_objects *obj;

	obj = scene->objects;
	while (obj)
	{
		if (obj->material.emission_power == 2.0f)
		{
			obj = obj->next;
			continue;
		}
		show_boundary(scene, get_boundary(obj), (t_vec3f){1, 1, 1});
		obj = obj->next;
	}
}

// t_hitInfo	trace_ray(t_scene *scene, t_ray ray)
// {
// 	t_hitInfo	temp_hit;
// 	t_objects	*temp_object;
// 	t_hitInfo	closest_hit;

// 	temp_object = scene->objects;
// 	closest_hit.distance = -1.0f;
// 	while (temp_object)
// 	{
// 		temp_hit = hit_objects(ray, temp_object);
// 		if (temp_hit.distance > 0.0f && (temp_hit.distance < closest_hit.distance || closest_hit.distance == -1.0f))
// 		{
// 			closest_hit = temp_hit;
// 			closest_hit.obj = temp_object;
// 		}
// 		temp_object = temp_object->next;
// 	}
// 	if (closest_hit.distance == -1.0f)
// 		return (closest_hit);
// 	if (closest_hit.obj->type == OBJ_PORTAL)
// 		ray = portal_ray(scene, &closest_hit, ray);
// 	return (closest_hit);
// }

t_hitInfo	octree_trace_ray_bis(t_scene *scene, t_octree *octree, t_ray ray)
{
	t_hitInfo closest_hit;
	t_hitInfo temp_hit;

	int has_hit = boxIntersection(ray, octree->boundary.origin, octree->boundary.size);
	if (!has_hit)
		return (closest_hit);
	closest_hit = hit_objects(ray, octree->objects);
	if (closest_hit.distance >= 0.0f)
		closest_hit.obj = octree->objects;
	if (octree->is_divided)
	{
		for(int i = 0; i < 8; i++)
		{
			if (octree->children[i]->objects)
			{
				temp_hit = octree_trace_ray_bis(scene, octree->children[i], ray);
				if (temp_hit.distance > 0.0f && (temp_hit.distance < closest_hit.distance || closest_hit.distance < 0.0f))
					closest_hit = temp_hit;
			}
		}
	}
	return (closest_hit);
}
void		create_octree(t_scene *scene)
{
	t_octree	*octree;

	octree = ft_calloc(1, sizeof(t_octree));
	if (!octree)
		rt_free_scene(scene);
	octree->boundary.origin = (t_vec3f){-100, -100, -100};
	octree->boundary.size = (t_vec3f){200, 200, 200};

	t_objects *obj = scene->objects;
	while (obj)
	{
		insert_octree(octree, obj);
		obj = obj->next;
	}
	scene->octree = octree;

	// show_boundary_objects(scene);
	// t_ray ray = (t_ray){(t_vec3f){0, 0, 0},(t_vec3f){0, 1, 0}};
	// t_hitInfo hit_info = octree_trace_ray_bis(scene, scene->octree, ray);
	// printf("hit distance: %f\n", hit_info.distance);
	// printf("%p\n", hit_info.obj->sphere);
	// create_sphere(scene, hit_info.position, (t_vec3f){1, 0, 0});

	// create_sphere(scene, ray.origin, (t_vec3f){1, 0, 0});
	// for(int i = 0; i < 5; i++)
		// create_sphere(scene, vec3f_add_v(ray.origin, vec3f_mul_f(vec3f_mul_f(ray.direction, i), 0.2)), (t_vec3f){1, 0.5, 0});

	// show_octree(scene, scene->octree, (t_vec3f){1,1,1}, 1);
}