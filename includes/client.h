/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:24:33 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/02 18:04:56 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
/*
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
*/
# include <arpa/inet.h>

void	rt_to_server(t_scene *scene, char *ip, char *port);
int		send_map(t_scene *scene, t_vec3f **map);
char	*buffer_to_str(t_buffer *buffer,int expect_size);
void	wait_for_server(t_scene *scene);
#endif

