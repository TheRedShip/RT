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

void		destroy_mlx(t_scene *scene)
{
	if(!scene->mlx->win)
	{
		mlx_destroy_display(scene->mlx->mlx);
		free(scene->mlx->mlx);
		free(scene->mlx);
		return ;
	}
	mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
	mlx_destroy_image(scene->mlx->mlx, scene->mlx->img.img);
	mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
	mlx_destroy_display(scene->mlx->mlx);
	mlx_loop_end(scene->mlx->mlx);
	free(scene->mlx->mlx);
	if (scene->mlx->acc_img)
		ft_free_tab((void **)(scene->mlx->acc_img));
	free(scene->mlx);
}

int			rt_free_scene(t_scene *scene)
{
	t_objects	*tmp;

	destroy_mlx(scene);
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
	exit(0);
	return (0);
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
	scene->mlx = ft_calloc(1, sizeof(t_mlx));
	scene->mlx->acc_img = init_acc_img(scene);
	create_window(&scene);
	scene->objects = NULL;
	if (!scene->ambient_light || !scene->camera || !scene->lights || !scene->mlx)
	{
		printf("Error: Memory allocation failed\n");
		rt_free_scene(scene);
	}
	scene->mlx->frame_index = 1;
	scene->mlx->is_acc = 1;
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
			printf("Origin: %f %f %f\n", objects->origin.x, objects->origin.y, objects->origin.z);
			printf("Diameter: %f\n", objects->sphere->diameter);
			printf("Color: %f %f %f\n", objects->material.color.x, objects->material.color.y, objects->material.color.z);	
		}
		else if (objects->plane)
		{
			printf("Plane\n");
			printf("Origin: %f %f %f\n", objects->origin.x, objects->origin.y, objects->origin.z);
			printf("Normal: %f %f %f\n", objects->plane->normal.x, objects->plane->normal.y, objects->plane->normal.z);
			printf("Color: %f %f %f\n", objects->material.color.x, objects->material.color.y, objects->material.color.z);			
		}
		else if (objects->cylinder)
		{
			printf("Cylinder\n");
			printf("Origin: %f %f %f\n", objects->origin.x, objects->origin.y, objects->origin.z);
			printf("Orientation: %f %f %f\n", objects->cylinder->orientation.x, objects->cylinder->orientation.y, objects->cylinder->orientation.z);
			printf("Diameter: %f\n", objects->cylinder->diameter);
			printf("Height: %f\n", objects->cylinder->height);
			printf("Color: %f %f %f\n", objects->material.color.x, objects->material.color.y, objects->material.color.z);
		}
		objects = objects->next;
	}
}

void	setup_mlx(t_scene *scene, t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 1L << 2, rt_free_scene, scene);
	mlx_hook(mlx->win, 2, 1L << 0, key_hook, scene);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_hook_move, scene);
	mlx_hook(mlx->win, 4, 1L << 2, mouse_hook_press, scene);
	mlx_hook(mlx->win, 5, 1L << 3, mouse_hook_release, scene);
	mlx_loop_hook(mlx->mlx, rt_render_scene, scene);
	mlx_loop(mlx->mlx);
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
	
	setup_mlx(scene, scene->mlx);
	return (0);
}
