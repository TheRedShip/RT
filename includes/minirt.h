/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:30 by marvin            #+#    #+#             */
/*   Updated: 2024/05/02 13:54:20 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1000
# define HEIGHT 1000

# define THREADS 16

# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>
# include <math.h>
# include <pthread.h>

# include "vector.h"
# include "scene_structures.h"
# include "postprocess.h"
# include "mlx.h"
# include "libft.h"
# include "objects.h"
# include "parsing.h"
# include "window.h"
# include "render.h"
# include "server.h"
# include "client.h"

t_vec3f	**init_img(t_scene *scene, int width, int height);
int		rt_free_scene(t_scene *scene, int ex);
void	destroy_mlx(t_scene *scene);
void	link_portals(t_scene *scene);
t_scene	*init_scene(char *name, t_scene *scene);

#endif
