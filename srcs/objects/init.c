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

int	init_texture(t_scene *s, t_material *material, char *p)
{
	t_texture	t;
	t_texture	b;
	char		*bu_pa;

	if (p[ft_strlen(p) - 2] == '\r')
		p[ft_strlen(p) - 2] = '\0';
	if (p[ft_strlen(p) - 1] == '\n')
		p[ft_strlen(p) - 1] = '\0';
	t.d.img = mlx_xpm_file_to_image(s->mlx->mlx, p, &t.width, &t.height);
	if (t.d.img == NULL || ft_strncmp(p + (ft_strlen(p) - 4), ".xpm", 4))
		return (printf("Error: Texture not found : %s/%s\n", getenv("PWD"), p));
	t.exist = 1;
	t.d.addr = mlx_get_data_addr(t.d.img, &t.d.bpp, &t.d.size, &t.d.endian);
	material->texture = t;
	p[ft_strlen(p) - 4] = '\0';
	bu_pa = ft_strjoin(p, "_bump.xpm", "", 0);
	b.d.img = mlx_xpm_file_to_image(s->mlx->mlx, bu_pa, &b.width, &b.height);
	free(bu_pa);
	if (b.d.img == NULL)
		return (0);
	b.exist = 1;
	b.d.addr = mlx_get_data_addr(b.d.img, &b.d.bpp, &b.d.size, &b.d.endian);
	material->bump_map = b;
	return (0);
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
