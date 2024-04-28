/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:36:43 by marvin            #+#    #+#             */
/*   Updated: 2024/04/28 22:27:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTPROCESS_H
# define POSTPROCESS_H

#include "minirt.h"

t_vec3f	**bloom(t_scene *scene, t_vec3f **image);

#endif