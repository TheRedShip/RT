/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:49 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 19:09:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		rt_free_scene(t_scene *scene)
{
	t_objects	*tmp;

	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->camera)
		free(scene->camera);
	if (scene->lights)
		free(scene->lights);
	while (scene->objects)
	{
		tmp = scene->objects;
		scene->objects = scene->objects->next;
		if (tmp->sphere)
			free(tmp->sphere);
		else if (tmp->plane)
			free(tmp->plane);
		else if (tmp->cylinder)
			free(tmp->cylinder);
		free(tmp);
	}
	free(scene);
	exit(1);
}

t_scene		*init_scene(void)
{
	t_scene *scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	scene->lights = ft_calloc(1, sizeof(t_light));
	scene->objects = NULL;
	if (!scene->ambient_light || !scene->camera || !scene->lights)
	{
		printf("Error: Memory allocation failed\n");
		rt_free_scene(scene);
	}
	return (scene);
}

void	show_objects(t_scene *scene)
{
	t_objects	*objects;

	objects = scene->objects;
	while (objects)
	{
		if (objects->sphere)
		{
			printf("Sphere\n");
			printf("Origin: %f %f %f\n", objects->sphere->origin.x, objects->sphere->origin.y, objects->sphere->origin.z);
			printf("Diameter: %f\n", objects->sphere->diameter);
			printf("Color: %d %d %d\n", objects->sphere->color.x, objects->sphere->color.y, objects->sphere->color.z);
		}
		else if (objects->plane)
		{
			printf("Plane\n");
			printf("Origin: %f %f %f\n", objects->plane->origin.x, objects->plane->origin.y, objects->plane->origin.z);
			printf("Normal: %f %f %f\n", objects->plane->normal.x, objects->plane->normal.y, objects->plane->normal.z);
			printf("Color: %d %d %d\n", objects->plane->color.x, objects->plane->color.y, objects->plane->color.z);
		}
		else if (objects->cylinder)
		{
			printf("Cylinder\n");
			printf("Origin: %f %f %f\n", objects->cylinder->origin.x, objects->cylinder->origin.y, objects->cylinder->origin.z);
			printf("Orientation: %f %f %f\n", objects->cylinder->orientation.x, objects->cylinder->orientation.y, objects->cylinder->orientation.z);
			printf("Diameter: %f\n", objects->cylinder->diameter);
			printf("Height: %f\n", objects->cylinder->height);
			printf("Color: %d %d %d\n", objects->cylinder->color.x, objects->cylinder->color.y, objects->cylinder->color.z);
		}
		objects = objects->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene		*scene;

	if (argc != 2)
	{
		printf("Usage: %s scenes/<file.rt>\n", argv[0]);
		return (1);
	}
	scene = init_scene();
	if (scene == NULL)
		exit(1);
	rt_parse(argv[1], &scene);
	printf("Parsing successful\n");
	show_objects(scene);
	rt_free_scene(scene);
	return (0);
}
