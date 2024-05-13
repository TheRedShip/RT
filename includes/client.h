/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:24:33 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/13 01:21:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <arpa/inet.h>

void	rt_to_server(t_scene *scene, char *ip, char *port);
void	render_server(t_scene *scene);

int		send_img(t_scene *scene, t_vec3f **img);
char	*buffer_to_str(t_buffer *buffer, int expect_size, t_scene *scene);

int		open_client_socket(char *ip, uint16_t port);
int		check_scene_data(int dest_fd, t_scene *scene, int force);

#endif
