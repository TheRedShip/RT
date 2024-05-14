/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:23:35 by marvin            #+#    #+#             */
/*   Updated: 2024/03/31 21:42:14 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		init_texture(t_scene *s, t_material *material, char *pa)
{
	t_texture	t;
	t_texture	b;
	char		*bu_pa;

	if (pa[ft_strlen(pa) - 2] == '\r')
		pa[ft_strlen(pa) - 2] = '\0';
	if (pa[ft_strlen(pa) - 1] == '\n')
		pa[ft_strlen(pa) - 1] = '\0';
	t.data.img = mlx_xpm_file_to_image(s->mlx->mlx, pa, &t.width, &t.height);
	if (t.data.img == NULL || ft_strncmp(pa + (ft_strlen(pa) - 4), ".xpm", 4))
		printf("Error: Texture not found : %s/%s\n", getenv("PWD"), pa);
	if (t.data.img == NULL || ft_strncmp(pa + (ft_strlen(pa) - 4), ".xpm", 4))
		rt_free_scene(s, 1);
	t.exist = 1;
	t.data.addr = mlx_get_data_addr(t.data.img, &t.data.bits_per_pixel, \
									&t.data.line_length, &t.data.endian);
	material->texture = t;
	pa[ft_strlen(pa) - 4] = '\0';
	bu_pa = ft_strjoin(pa, "_bump.xpm", "", 0);
	printf("Bump map path: %s\n", bu_pa);
	b.data.img = mlx_xpm_file_to_image(s->mlx->mlx, bu_pa, &b.width, &b.height);
	free(bu_pa);
	if (b.data.img == NULL)
		return ;
	printf("Bump map found\n");
	b.exist = 1;
	b.data.addr = mlx_get_data_addr(b.data.img, &b.data.bits_per_pixel, \
									&b.data.line_length, &b.data.endian);
	material->bump_map = b;
}

t_material	init_material(void)
{
	t_material	mat;

	mat.color = (t_vec3f){0.0f, 0.0f, 0.0f};
	mat.type = MAT_LAMBERT;
	mat.checkered = 0;
	mat.roughness = 1.0f;
	mat.texture.exist = 0;
	mat.specular_probs = 0.0f;
	mat.emission_power = 0.0f;
	mat.refraction_index = 1.0f;
	mat.texture.exist = 0;
	mat.bump_map.exist = 0;
	return (mat);
}

void	allocate_object(t_scene *scene, t_objects *obj, int type)
{
	if (type == OBJ_SPHER)
		obj->sphere = ft_calloc(1, sizeof(t_sphere));
	else if (type == OBJ_PLANE)
		obj->plane = ft_calloc(1, sizeof(t_plane));
	else if (type == OBJ_CYLIN)
		obj->cylinder = ft_calloc(1, sizeof(t_cylinder));
	else if (type == OBJ_QUADS)
		obj->quad = ft_calloc(1, sizeof(t_quad));
	else if (type == OBJ_ELLIP)
		obj->ellipse = ft_calloc(1, sizeof(t_ellipse));
	else if (type == OBJ_PORTA)
		obj->portal = ft_calloc(1, sizeof(t_portal));
	else if (type == OBJ_TRIAN)
		obj->triangle = ft_calloc(1, sizeof(t_triangle));
	if (!(obj->sphere || obj->plane || obj->cylinder || obj->quad \
		|| obj->ellipse || obj->portal || obj->triangle))
		rt_free_scene(scene, 1);
}

t_objects	*rt_add_objects(t_scene *scene, char *type)
{
	int			i;
	t_objects	*objects;
	static char	*types[8] = {"sp", "pl", "cy", "qd", "el", "po", "tr", NULL};

	objects = ft_calloc(1, sizeof(t_objects));
	if (!objects)
		rt_free_scene(scene, 1);
	i = -1;
	while (types[++i] != NULL && ft_strncmp(type, types[i], 2))
		;
	*objects = (t_objects){.type = i, .material = init_material()};
	rt_add_objlst(scene, objects);
	allocate_object(scene, objects, i);
	return (objects);
}
