/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:24:09 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 17:24:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

typedef enum e_obj_type
{
	OBJ_SPHER		= 0,
	OBJ_PLANE		= 1,
	OBJ_CYLIN		= 2,
	OBJ_QUADS		= 3,
	OBJ_ELLIP		= 4,
	OBJ_PORTA		= 5,
	OBJ_TRIAN		= 6
}	t_obj_type;

typedef enum e_mat_type
{
	MAT_LAMBERT		= 0,
	MAT_DIELECTRIC	= 1
}	t_mat_type;

typedef struct s_texture
{
	int			exist;
	char		*path;
	t_data		data;
	int			width;
	int			height;
}				t_texture;

typedef struct s_material
{
	int			type;
	t_vec3f		color;
	t_texture	texture;
	t_texture	bump_map;
	int			checkered;
	float		roughness;
	float		specular_probs;
	float		emission_power;
	float		refraction_index;
}				t_material;

typedef struct s_objects
{
	int					type;
	t_vec3f				origin;
	t_quad				*quad;
	t_plane				*plane;
	t_sphere			*sphere;
	t_portal			*portal;
	t_ellipse			*ellipse;
	t_triangle			*triangle;
	t_cylinder			*cylinder;
	t_material			material;
	struct s_objects	*next;
	struct s_objects	*next_bvh;
}				t_objects;

typedef struct s_hit_info	t_hit_info;
typedef struct s_ray		t_ray;

t_hit_info	hit_objects(t_ray ray, t_objects *obj);
t_hit_info	hit_sphere(t_ray r, t_objects *obj, t_sphere *sp);
t_hit_info	hit_quad(t_ray ray, t_objects *obj, t_quad *quad);
t_hit_info	hit_plane(t_ray ray, t_objects *obj, t_plane *plane);
t_hit_info	hit_ellipse(t_ray ray, t_objects *obj, t_ellipse *el);

void		link_portals(t_scene *scene);

t_material	init_material(void);
void		init_texture(t_scene *scene, t_material *material, char *path);

t_vec2f		get_quad_uv(t_hit_info hit_info);
t_vec2f		get_plane_uv(t_hit_info hit_info);
t_vec2f		get_sphere_uv(t_hit_info hit_info);
t_vec3f		get_texture_color(t_hit_info hit_info, int is_specular);
t_vec3f		get_bump_normal(t_hit_info hit_info, t_texture bump);

void		rt_lstobj_addback(t_objects **lst, t_objects *new);
t_objects	*rt_add_objects(t_scene *scene, char *type);
void		rt_add_objlst(t_scene *scene, t_objects *objects);

#endif