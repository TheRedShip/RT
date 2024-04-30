/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:24:33 by tomoron           #+#    #+#             */
/*   Updated: 2024/04/30 02:17:57 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFFER_SIZE 16384
#define MAX_BUFFER 16384


typedef struct s_threads
{
	pthread_t			id;
	struct s_threads	*prev;
}	t_threads;

typedef struct s_buffer
{
	char				str[BUFFER_SIZE];
	int					nb;
	int					len;
	struct s_buffer		*next;
	struct s_buffer		*prev;
}	t_buffer;

extern int g_stop;

void wait_clients(int socket);
int	add_buffer(t_buffer **buffer);
void	free_buffer(t_buffer *buffer);
void	copy_buffer(char *res, t_buffer *buffer);
unsigned long int get_buffer_str_len(t_buffer *buffer);
int	add_thread(t_threads **thrds);
void	wait_threads(t_threads *thrds);

#endif

