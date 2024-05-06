/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:36:43 by marvin            #+#    #+#             */
/*   Updated: 2024/05/06 18:32:17 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTPROCESS_H
# define POSTPROCESS_H

# include "minirt.h"

t_vec3f	**bloom(t_scene *scene, t_vec3f **image);

#endif