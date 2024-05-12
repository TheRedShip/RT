/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:35:16 by ycontre           #+#    #+#             */
/*   Updated: 2024/05/12 18:55:54 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_info	basic_trace_ray(t_scene *scene, t_ray ray)
{
	t_hit_info	temp_hit;
	t_objects	*temp_object;
	t_hit_info	closest_hit;

	temp_object = scene->objects;
	closest_hit.distance = -1.0f;
	while (temp_object)
	{
		temp_hit = hit_objects(ray, temp_object);
		if (temp_hit.distance > 0.0f
			&& (temp_hit.distance < closest_hit.distance
				|| closest_hit.distance < 0.0f))
		{
			closest_hit = temp_hit;
			closest_hit.obj = temp_object;
		}
		temp_object = temp_object->next;
	}
	if (closest_hit.distance > 0.0f && closest_hit.obj->type == OBJ_PORTA)
		ray = portal_ray(scene, &closest_hit, ray);
	return (closest_hit);
}

t_hit_info	closest_hit_in_bvh(t_bvh *bvh, t_ray ray)
{
	t_hit_info	hit_info;
	t_hit_info	tmp_hit;
	t_list		*obj;

	hit_info.distance = -1.0f;
	obj = bvh->objects;
	while (obj)
	{
		tmp_hit = hit_objects(ray, (t_objects *)obj->content);
		if (tmp_hit.distance >= 0 && (tmp_hit.distance < hit_info.distance || hit_info.distance < 0))
		{
			hit_info = tmp_hit;
			hit_info.obj = (t_objects *)obj->content;
		}
		obj = obj->next;
	}
	return (hit_info);
}

t_hit_info	bvh_trace_ray(t_bvh *bvh, t_ray ray)
{
	t_hit_info	hit_info;
	t_hit_info	hit_0;
	t_hit_info	hit_1;

	hit_info.distance = -1.0f;
	if (!box_intersection(ray, bvh->boundary.origin, bvh->boundary.size))
		return (hit_info);
	if (bvh->leaf)
		return (closest_hit_in_bvh(bvh, ray));
	if (bvh->divided)
	{
		hit_0 = bvh_trace_ray(bvh->children[0], ray);
		hit_1 = bvh_trace_ray(bvh->children[1], ray);
		if (hit_0.distance >= 0.0f && (hit_1.distance < 0.0f || hit_0.distance <= hit_1.distance))
			return (hit_0);
		if (hit_1.distance >= 0.0f && (hit_0.distance < 0.0f || hit_1.distance < hit_0.distance))
			return (hit_1);
	}
	return (hit_info);
}

t_hit_info	trace_ray(t_scene *scene, t_ray ray)
{
	if (scene->kdtree->is_bvh)
		return (bvh_trace_ray(scene->bvh, ray));
	return (basic_trace_ray(scene, ray));
}

t_vec3f	per_pixel(t_scene *scene, t_vec2f uv, t_threads *thread)
{
	t_hit_info	hit_info;
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
		hit_info = trace_ray(scene, ray);
		if (hit_info.distance < 0.0f)
			l_c[0] = v_add_v(l_c[0], v_mul_f(scene->ambient_light->color,
						scene->ambient_light->ratio));
		if (hit_info.distance < 0.0f)
			break ;
		ray = new_ray(hit_info, ray, thread, &is_specular);
		calcul_light(hit_info, scene, &l_c[0], &l_c[1], is_specular);
		if (hit_info.obj->material.emission_power > 0.0f)
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

void	rt_render_image(t_vec3f **image, t_data *img)
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
			put_pixel(img, pos.x, pos.y, rgb_to_hex(color));
			pos.x++;
		}
		pos.y++;
	}
}

int	rt_render_scene(t_scene *scene)
{
	u_int64_t	start;
	t_threads	threads[THREADS];

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

	start = get_time();
	for (int i = 0; i < THREADS; i++)
	{
		threads[i].id = i;
		threads[i].scene = scene;
		pthread_create(&(threads[i].thread), NULL, draw, (threads + i));
	}
	for (int i = 0; i < THREADS; i++)
		pthread_join(threads[i].thread, NULL);
	if (!scene->server.ip)
		rt_render_image(bloom(scene, scene->mlx->final_img), &scene->mlx->img);
	if (scene->server.ip)
	{
		if (!send_img(scene, scene->mlx->acc_img))
		{
			printf("\nwaiting for server...\n");
			wait_for_server(scene);
			printf("server back\n");
		}
	}
	else
		mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win,
			scene->mlx->img.img, 0, 0);
	if(scene->server.ip)
		printf("Send time : %lu ms, ", scene->server.send_time);
	printf("Rendering scene : %lu ms %d            \r", get_time() - start,
		scene->mlx->frame_index);
	fflush(stdout);
	if (scene->mlx->is_acc)
		scene->mlx->frame_index++;
	else
		scene->mlx->frame_index = 1;
	return (0);
}
