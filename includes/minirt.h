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

# include <stdio.h>

# include "utils_struct.h"
# include "parsing_struct.h"
# include "scene_structures.h"
# include "mlx.h"
# include "libft.h"
# include "objects.h"
# include "parsing.h"
# include "window.h"

# define WIDTH 800
# define HEIGHT 600

int		rt_free_scene(t_scene *scene);

#endif