/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:51:27 by marvin            #+#    #+#             */
/*   Updated: 2024/05/12 17:51:27 by marvin           ###   ########.fr       */
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

void	rt_free_obj(t_scene *scene)
{
	t_objects	*tmp;

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
}

int	rt_free_scene(t_scene *scene, int ex)
{
	free(scene->ambient_light);
	free(scene->bloom);
	free(scene->camera);
	free(scene->kdtree);
	free(scene->lights);
	free(scene->name);
	rt_free_bvh(scene->bvh);
	rt_free_obj(scene);
	if (ex)
	{
		destroy_mlx(scene);
		free(scene);
		exit(0);
	}
	return (0);
}
