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
			printf("Sphere\n");
		else if (objects->plane)
			printf("Plane\n");
		else if (objects->cylinder)
			printf("Cylinder\n");
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
