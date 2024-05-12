/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:35:16 by ycontre           #+#    #+#             */
/*   Updated: 2024/05/12 19:48:39 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	per_pixel(t_scene *scene, t_vec2f uv, t_threads *thread)
{
	t_hit_info	hit;
	t_vec3f		l_c[2];
	t_ray		ray;
	int			is_specular;
	int			i;

	ray.origin = scene->camera->origin;
	ray.direction = calculate_ray_direction(scene, (t_vec3f){uv.x, uv.y, -1});
	l_c[0] = (t_vec3f){0.0f, 0.0f, 0.0f};
	l_c[1] = (t_vec3f){1.0f, 1.0f, 1.0f};
	i = -1;
	while (++i < (!scene->mouse.is_pressed * (scene->camera->bounce - 2)) + 2)
	{
		hit = trace_ray(scene, ray);
		if (hit.distance < 0.0f)
			l_c[0] = v_add_v(l_c[0], v_mul_f(scene->ambient_light->color,
						scene->ambient_light->ratio));
		if (hit.distance < 0.0f)
			break ;
		ray = new_ray(hit, ray, thread, &is_specular);
		calcul_light(hit, scene, (t_vec3f *[2]){&l_c[0], &l_c[1]}, is_specular);
		if (hit.obj->material.emission_power > 0.0f)
			break ;
	}
	return (v_mul_v(l_c[0], l_c[1]));
}

void	*draw(void *thread_ptr)
{
	int			p[2];
	t_vec2f		uv;
	t_scene		*s;
	t_threads	*thread;

	thread = (t_threads *)thread_ptr;
	s = thread->scene;
	p[1] = thread->id;
	while (p[1] < HEIGHT)
	{
		p[0] = 0;
		while (p[0] < WIDTH)
		{
			uv = get_uv(thread, p[0], p[1]);
			s->mlx->acc_img[p[1]][p[0]] = v_add_v(s->mlx->acc_img[p[1]][p[0]],
					per_pixel(s, uv, thread));
			s->mlx->final_img[p[1]][p[0]] = v_div_f(s->mlx->acc_img[p[1]][p[0]],
					(float)s->mlx->frame_index);
			p[0]++;
		}
		p[1] += THREADS;
	}
	return (NULL);
}

void	rt_render_image(t_scene *scene, t_vec3f **image)
{
	t_vec3f	color;
	t_vec2f	pos;

	pos.y = 0;
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			color = image[(int)pos.y][(int)pos.x];
			color = clamp(color, 0.0f, 1.0f);
			put_pixel(&scene->mlx->img, pos.x, pos.y, rgb_to_hex(color));
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win,
		scene->mlx->img.img, 0, 0);
}

void	render_server(t_scene *scene)
{
	if (!send_img(scene, scene->mlx->acc_img))
	{
		printf("\nwaiting for server...\n");
		wait_for_server(scene);
		printf("server back\n");
	}
}

void	rt_init_render(t_scene *scene)
{
	if (scene->mlx->frame_index == 1)
	{
		ft_free_tab((void **)(scene->mlx->acc_img));
		scene->mlx->acc_img = init_img(scene, WIDTH, HEIGHT);
		if (!scene->server.ip)
			ft_memset(scene->mlx->img.addr, 0, WIDTH * HEIGHT * 4);
	}
	apply_rotation_matrix_x(scene->camera->direction.x,
		scene->camera->rotation_matrix_x);
	apply_rotation_matrix_y(scene->camera->direction.y,
		scene->camera->rotation_matrix_y);
}

int	rt_render_scene(t_scene *scene)
{
	int			i;
	u_int64_t	t;
	t_threads	threads[THREADS];

	rt_init_render(scene);
	t = get_time();
	i = -1;
	while (++i < THREADS)
	{
		threads[i].id = i;
		threads[i].scene = scene;
		pthread_create(&(threads[i].thread), NULL, draw, (threads + i));
	}
	while (--i >= 0)
		pthread_join(threads[i].thread, NULL);
	if (scene->server.ip)
		render_server(scene);
	else
		rt_render_image(scene, bloom(scene, scene->mlx->final_img));
	if (scene->server.ip)
		printf("Send time : %lu ms, ", scene->server.send_time);
	printf("Rendering : %lu ms %d\r", get_time() - t, scene->mlx->frame_index);
	fflush(stdout);
	scene->mlx->frame_index = scene->mlx->frame_index * scene->mlx->is_acc + 1;
	return (0);
}
