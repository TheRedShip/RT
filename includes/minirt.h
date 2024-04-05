/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:30 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 19:09:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1000
# define HEIGHT 1000

# define THREADS 16

# include <stdio.h>
# include <sys/time.h>
# include <math.h>
# include <pthread.h>

# include "vector.h"
# include "parsing_struct.h"
# include "scene_structures.h"
# include "mlx.h"
# include "libft.h"
# include "objects.h"
# include "parsing.h"
# include "window.h"
# include "render.h"


t_vec3f	**init_acc_img(t_scene *scene);
int		rt_free_scene(t_scene *scene);

int	ft_rand(int i);

#endif