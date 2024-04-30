/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:24:33 by tomoron           #+#    #+#             */
/*   Updated: 2024/04/30 20:19:21 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>

# define SOCKET_BUFFER_SIZE 16384
# define MAX_BUFFER 16384


typedef struct s_srv_threads
{
	pthread_t				id;
	struct s_srv_threads	*prev;
}	t_srv_threads;

typedef struct s_buffer
{
	char				str[SOCKET_BUFFER_SIZE];
	int					nb;
	int					len;
	struct s_buffer		*next;
	struct s_buffer		*prev;
}	t_buffer;

typedef struct s_thread_data
{
	int fd;
	t_scene	*scene;
}	t_thread_data;

void			wait_clients(t_scene *scene, int socket);
int				add_buffer(t_buffer **buffer);
void			free_buffer(t_buffer *buffer);
void			copy_buffer(char *res, t_buffer *buffer);
unsigned int	get_buffer_str_len(t_buffer *buffer);
int				add_thread(t_srv_threads **thrds);
void			wait_threads(t_srv_threads *thrds);
int				start_server(t_scene *scene, char *port_str);

#endif

