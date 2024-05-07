/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:36:43 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 12:32:34 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTPROCESS_H
# define POSTPROCESS_H

# include "minirt.h"

t_vec3f	**add_img(t_vec3f **treshold, t_vec3f **image);
void	dup_img(t_vec3f **image, t_vec3f **image2, t_vec2f resolution);

t_vec3f **sample(t_vec3f **image, int mip_num, int blur_size);
t_vec3f	**gaussian_blur(t_vec3f **image, t_vec2f resolution, int blur_size);

t_vec3f	**bloom(t_scene *scene, t_vec3f **image);

#endif
