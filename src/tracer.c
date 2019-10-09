/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:40 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/09 16:58:54 by lglover          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	hit_objects(t_scene scene, t_ray ray, t_hit *hit)
{
	hit->d = MAX_DIST;
	hit->collided = FALSE;
	check_planes(scene, ray, hit);
	check_spheres(scene, ray, hit);
	check_cylinder(scene, ray, hit);
	check_cone(scene, ray, hit);
}

void	trace_ray(t_app *app, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	t_scene	scene;

	scene = *app->scenes;
	ray.o = app->pos;
	ray.d = ray_direction(app, x, y);
	hit_objects(scene, ray, &hit);
	if (hit.collided && hit.d < INFINITY)
	{
		process_lights(scene, ray, &hit);
		set_pixel(app->sdl->surface, x, y, hit.m.c);
	}
	else
		set_pixel(app->sdl->surface, x, y, BLACK);
}

void	*init_thread(void *ptr)
{
	t_thread_data	data;
	int				x;
	int				y;

	data = *(t_thread_data *)(ptr);
	y = data.sy;
	while (y < data.ey)
	{
		x = data.sx;
		while (x < data.ex)
			trace_ray(data.app, x++, y);
		y++;
	}
	return (NULL);
}

void	trace_rays(t_app *app)
{
	int				tr_count;
	t_thread_data	*tr_data;
	int				tr_id;

	tr_count = 16;
	tr_data = (t_thread_data *)malloc(sizeof(t_thread_data) * tr_count);
	tr_id = 0;
	while (tr_id < tr_count)
	{
		tr_data[tr_id].app = app;
		tr_data[tr_id].sx = 0;
		tr_data[tr_id].ex = WIDTH;
		tr_data[tr_id].sy = tr_id * (HEIGHT / tr_count);
		tr_data[tr_id].ey = (tr_id + 1) * (HEIGHT / tr_count);
		pthread_create(&tr_data[tr_id].tr, NULL, init_thread, &tr_data[tr_id]);
		tr_id++;
	}
	tr_id = 0;
	while (tr_id < tr_count)
	{
		pthread_join(tr_data[tr_id].tr, NULL);
		tr_id++;
	}
	free(tr_data);
}
