/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:49 by marvin            #+#    #+#             */
/*   Updated: 2024/05/02 19:00:49 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_mlx(t_scene *scene)
{
	if (!scene->mlx)
		return ;
	if (scene->mlx->win)
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
	if (scene->mlx->img.img)
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img.img);
	if (scene->mlx->win)
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
	if (scene->mlx->mlx)
		mlx_destroy_display(scene->mlx->mlx);
	if (scene->mlx->mlx)
		mlx_loop_end(scene->mlx->mlx);
	free(scene->mlx->mlx);
	if (scene->mlx->acc_img)
		ft_free_tab((void **)(scene->mlx->acc_img));
	if (scene->mlx->final_img)
		ft_free_tab((void **)(scene->mlx->final_img));
	if (scene->mlx->postpro_img)
		ft_free_tab((void **)(scene->mlx->postpro_img));
	free(scene->mlx);
}

void	rt_free_bvh(t_bvh *bvh)
{
	t_list	*tmp;

	if (!bvh)
		return ;
	if (bvh->divided)
	{
		rt_free_bvh(bvh->children[1]);
		rt_free_bvh(bvh->children[0]);
	}
	if (bvh->obj_count > 0)
	{
		while (bvh->objects)
		{
			tmp = bvh->objects;
			bvh->objects = bvh->objects->next;
			free(tmp);
		}
	}
	free(bvh);
}

int	rt_free_scene(t_scene *scene, int ex)
{
	t_objects	*tmp;

	free(scene->ambient_light);
	free(scene->bloom);
	free(scene->camera);
	free(scene->kdtree);
	free(scene->lights);
	free(scene->name);
	rt_free_bvh(scene->bvh);
	while (scene->objects)
	{
		tmp = scene->objects;
		scene->objects = scene->objects->next;
		if (tmp->material.texture.exist == 1)
			mlx_destroy_image(scene->mlx->mlx, tmp->material.texture.data.img);
		free(tmp->sphere);
		free(tmp->plane);
		free(tmp->cylinder);
		free(tmp->ellipse);
		free(tmp->quad);
		free(tmp->portal);
		free(tmp->triangle);
		free(tmp);
	}
	if (ex)
	{
		destroy_mlx(scene);
		free(scene);
		exit(0);
	}
	return (0);
}

t_scene	*init_scene(char *name, t_scene *scene)
{
	if (!scene)
		scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		exit(0);
	scene->ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	scene->lights = ft_calloc(1, sizeof(t_light));
	scene->bloom = ft_calloc(1, sizeof(t_bloom));
	scene->mlx = ft_calloc(1, sizeof(t_mlx));
	scene->kdtree = ft_calloc(1, sizeof(t_kd_tree));
	scene->name = ft_strdup(name);
	scene->mlx->acc_img = init_img(scene, WIDTH, HEIGHT);
	scene->mlx->final_img = init_img(scene, WIDTH, HEIGHT);
	scene->mlx->postpro_img = init_img(scene, WIDTH, HEIGHT);
	scene->objects = NULL;
	if (!scene->ambient_light || !scene->camera || !scene->lights || \
		!scene->mlx || !scene->bloom || !scene->name || !scene->kdtree)
	{
		printf("Error: Memory allocation failed\n");
		rt_free_scene(scene, 1);
	}
	scene->mlx->is_acc = 1;
	scene->mlx->is_bloom = 0;
	scene->mlx->frame_index = 1;
	scene->mlx->antialiasing = 1;
	return (scene);
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

void	link_portals(t_scene *scene)
{
	t_objects	*obj;
	t_objects	*tmp;
	t_objects	*start;

	obj = scene->objects;
	start = obj;
	while (obj)
	{
		if (obj->type == OBJ_PORTA)
		{
			tmp = start;
			while (tmp && !obj->portal->linked_portal)
			{
				if (tmp->type == OBJ_PORTA
					&& obj->portal->linked_id == tmp->portal->portal_id)
					obj->portal->linked_portal = tmp;
				tmp = tmp->next;
			}
		}
		obj = obj->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene		*scene;

	if (argc < 2 || argc > 4)
	{
		printf("Usage:	%s scenes/<file.rt> [IP [PORT]]\n", argv[0]);
		printf("		%s scenes/<file.rt> server [PORT]\n", argv[0]);
		return (1);
	}
	scene = init_scene(argv[1], 0);
	if (scene == NULL)
		return (1);
	create_window(scene, argc >= 3 && ft_strcmp(argv[2], "server"));
	rt_parse(argv[1], scene);
	printf("Parsing successful\n");
	if (scene->kdtree->is_bvh)
		create_bvh(scene);
	printf("Parsing complete\n");
	link_portals(scene);
	if (argc == 4 && !ft_strcmp(argv[2], "server"))
		return (start_server(scene, argv[3]));
	if (argc == 3 && !ft_strcmp(argv[2], "server"))
		return (start_server(scene, "25565"));
	if (argc == 2)
		setup_mlx(scene, scene->mlx);
	else if (argc == 3)
		rt_to_server(scene, argv[2], "25565");
	else if (argc == 4)
		rt_to_server(scene, argv[2], argv[3]);
	return (0);
}
