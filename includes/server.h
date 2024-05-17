/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:24:33 by tomoron           #+#    #+#             */
/*   Updated: 2024/05/15 20:23:47 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <signal.h>

# define SOCKET_BUFFER_SIZE 100000
# define MAX_BUFFER 50000
# define MAX_SEND_TIME 500

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
	int		fd;
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
pthread_t		init_server_hooks(t_scene *scene);
int				get_stopped(t_scene *scene);
void			reset_img(t_vec3f **img);
long unsigned	get_avg_time(t_scene *scene);
float			get_avg_speed(t_scene *scene);
void			set_stopped(t_scene *scene);
int				mouse_hook_move_server(int x, int y, t_scene *scene);
int				mouse_hook_release_server(int button, int x, int y, \
					t_scene *scene);
int				mouse_hook_press_server(int button, int x, int y, \
					t_scene *scene);
int				server_loop_hook(void *data);
int				server_key_hook(int key, void *data);
void			*handle_client(void *data_ptr);

#endif
