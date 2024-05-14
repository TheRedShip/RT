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

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <libgen.h>

# include "libft.h"

# include "vector.h"
# include "scene_structures.h"
# include "bvh.h"
# include "postprocess.h"
# include "mlx.h"
# include "objects.h"
# include "parsing.h"
# include "window.h"
# include "render.h"
# include "server.h"
# include "client.h"

u_int64_t	get_time(void);

int			rt_free_scene(t_scene *scene, int ex);
t_scene		*init_scene(char *name, t_scene *scene);

#endif
