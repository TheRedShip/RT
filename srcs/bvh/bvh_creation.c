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

t_bvh	*b_node(t_vec3f origin, t_vec3f size)
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

void	sub_divide(t_bvh *bvh, int depth)
{
	t_vec3f	ori;
	t_vec3f	half;
	int		dim;

	if (bvh->divided)
		return ;
	bvh->divided = 1;
	ori = bvh->boundary.origin;
	dim = depth % 3;
	if (dim == 0)
		half = (t_vec3f){bvh->boundary.size.x, bvh->boundary.size.y / 2.0f, \
							bvh->boundary.size.z};
	if (dim == 0)
		bvh->children[1] = b_node(v_add_v(ori, (t_vec3f){0, half.y, 0}), half);
	if (dim == 1)
		half = (t_vec3f){bvh->boundary.size.x / 2.0f, bvh->boundary.size.y, \
							bvh->boundary.size.z};
	if (dim == 1)
		bvh->children[1] = b_node(v_add_v(ori, (t_vec3f){half.x, 0, 0}), half);
	if (dim == 2)
		half = (t_vec3f){bvh->boundary.size.x, bvh->boundary.size.y, \
							bvh->boundary.size.z / 2.0f};
	if (dim == 2)
		bvh->children[1] = b_node(v_add_v(ori, (t_vec3f){0, 0, half.z}), half);
	bvh->children[0] = b_node(ori, half);
}

void	add_object_bvh(t_bvh *bvh, t_objects *obj)
{
	bvh->leaf = 1;
	bvh->obj_count++;
	ft_lstadd_back(&bvh->objects, ft_lstnew((void *)obj));
	return ;
}

void	insert_bvh(t_bvh *bvh, t_objects *object, int depth, t_scene *s)
{
	t_list	*t;

	if (depth > MAX_RECURSIVE)
		printf("Error: kd_tree: not enough objects per subdivision\n");
	if (depth > MAX_RECURSIVE)
		rt_free_scene(s, 1);
	if (!boundary_intersect(bvh->boundary, object))
		return ;
	if (depth > 0 && (bvh->obj_count < s->kdtree->max_objects))
		return (add_object_bvh(bvh, object));
	sub_divide(bvh, depth);
	if (bvh->obj_count >= s->kdtree->max_objects && bvh->leaf)
	{
		bvh->leaf = 0;
		t = bvh->objects;
		while (t)
		{
			insert_bvh(bvh->children[0], (t_objects *)t->content, depth + 1, s);
			insert_bvh(bvh->children[1], (t_objects *)t->content, depth + 1, s);
			t = t->next;
		}
	}
	insert_bvh(bvh->children[0], object, depth + 1, s);
	insert_bvh(bvh->children[1], object, depth + 1, s);
	return ;
}

void	create_bvh(t_scene *scene)
{
	t_objects	*obj;

	scene->bvh = ft_calloc(1, sizeof(t_bvh));
	if (!scene->bvh)
		rt_free_scene(scene, 1);
	scene->bvh->boundary.origin = (t_vec3f){-400, -400, -400};
	scene->bvh->boundary.size = (t_vec3f){800, 800, 800};
	obj = scene->objects;
	while (obj)
	{
		if (obj->type != OBJ_PLANE)
			insert_bvh(scene->bvh, obj, 0, scene);
		obj = obj->next;
	}
	printf("KD-Tree created\n");
}
