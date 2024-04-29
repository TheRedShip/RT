/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:30 by marvin            #+#    #+#             */
/*   Updated: 2024/04/09 01:03:06 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1920
# define HEIGHT 1080

# define THREADS 16

# include <stdio.h>
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

t_vec3f	**init_img(t_scene *scene, int width, int height);
int		rt_free_scene(t_scene *scene);

#endif
