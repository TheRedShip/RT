/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:49 by marvin            #+#    #+#             */
/*   Updated: 2024/04/14 18:14:08 by tomoron          ###   ########.fr       */
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
	if (scene->mlx->final_img)
		ft_free_tab((void **)(scene->mlx->final_img));
	if (scene->mlx->postpro_img)
		ft_free_tab((void **)(scene->mlx->postpro_img));
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
		free(tmp->sphere);
		free(tmp->plane);
		free(tmp->cylinder);
		free(tmp->ellipse);
		free(tmp->quad);	
		free(tmp->portal);
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
	scene->mlx->acc_img = init_img(scene, WIDTH, HEIGHT);
	scene->mlx->final_img = init_img(scene, WIDTH, HEIGHT);
	scene->mlx->postpro_img = init_img(scene, WIDTH, HEIGHT);
	create_window(&scene);
	scene->objects = NULL;
	if (!scene->ambient_light || !scene->camera || !scene->lights || !scene->mlx)
	{
		printf("Error: Memory allocation failed\n");
		rt_free_scene(scene);
	}
	scene->mlx->frame_index = 1;
	scene->mlx->antialiasing = 1;
	scene->mlx->is_acc = 1;
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
	t_objects *obj;
	t_objects *tmp;
	t_objects *start;

	obj = scene->objects;
	start = obj;
	while(obj)
	{
		if(obj->type == OBJ_PORTAL)
		{
			tmp = start;
			while(tmp && !obj->portal->linked_portal)
			{
				if(tmp->type == OBJ_PORTAL
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

	if (argc != 2)
	{
		printf("Usage: %s scenes/<file.rt>\n", argv[0]);
		return (1);
	}
	scene = init_scene();
	if (scene == NULL)
		exit(1);
	rt_parse(argv[1], &scene);
	link_portals(scene);
	printf("Parsing successful\n");
	setup_mlx(scene, scene->mlx);
	return (0);
}
