/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:19:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/02 19:03:05 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "minirt.h"

# define KEY_ESCH	65307
# define KEY_FORW	119
# define KEY_BACK	115
# define KEY_ALIA	107
# define KEY_LEFT	97
# define KEY_RIGHT	100
# define KEY_UPE	101
# define KEY_DOWNA	113
# define KEY_ENTER	65293
# define CAM_UP		65362
# define CAM_DOWN	65364
# define CAM_LEFT	65361
# define CAM_RIGHT	65363
# define KEY_BLOOM	98

void			create_window(t_scene *scene, int headless);
void			put_pixel(t_data *data, int x, int y, int color);
unsigned int	get_pixel(t_data *img, int x, int y);

void			move_camera(t_scene *scene, t_vec3f movement);
int				key_move_hook(int keycode, t_scene *scene);
void			key_settings_hook(int keycode, t_scene *scene);

int				key_hook(int keycode, t_scene *scene);
int				mouse_hook_move(int x, int y, t_scene *scene);
int				mouse_hook_press(int button, int x, int y, t_scene *scene);
int				mouse_hook_release(int button, int x, int y, t_scene *scene);

#endif
