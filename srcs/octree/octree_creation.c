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
		printf("inserted\n");
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
void		show_octree(t_scene *scene, t_octree *octree, t_vec3f color)
{
	static int		octree_num = 0;
	
	if (octree->objects)
	{
		octree_num++;
		printf("octree_num: %d %f %f %f\n", octree_num, octree->objects->origin.x, octree->objects->origin.y, octree->objects->origin.z);
		show_boundary(scene, octree->boundary, color);
	}
	if (octree->is_divided)
	{
		for(int i = 0; i < 8; i++)
			show_octree(scene, octree->children[i], vec3f_mul_v(color, (t_vec3f){0.7, 0.4, 0.3}));
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

void		create_octree(t_scene *scene)
{
	t_octree	*octree;

	octree = ft_calloc(1, sizeof(t_octree));
	if (!octree)
		rt_free_scene(scene);
	octree->boundary.origin = (t_vec3f){-3, -3, -3};
	octree->boundary.size = (t_vec3f){6, 6, 6};

	t_objects *obj = scene->objects;
	while (obj)
	{
		if (obj->type != OBJ_SPHER)
		{
			obj = obj->next;
			continue;
		}
		insert_octree(octree, obj);
		obj = obj->next;
	}
	scene->octree = octree;

	show_boundary_objects(scene);
	show_octree(scene, scene->octree, (t_vec3f){1,1,1});
}