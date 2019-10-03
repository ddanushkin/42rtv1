#include "rt.h"

void	hit_objects(t_scene scene, t_ray ray, t_hit *hit)
{
	hit->d = INFINITY;
	hit->collided = FALSE;
	check_planes(scene, ray, hit);
	check_spheres(scene, ray, hit);
	check_cylinder(scene, ray, hit);
	check_cone(scene, ray, hit);
}

void	trace_ray(t_app *app, int scene_id, int x, int y)
{
	t_ray	ray;
	t_hit	hit;

	ray.o = app->pos;
	ray.d = ray_direction(app, x, y);
	hit_objects(app->scene[scene_id], ray, &hit);
	if (hit.collided && hit.d < INFINITY)
	{
		process_lights(app->scene[scene_id], ray, &hit);
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
			trace_ray(data.app, data.scene_id, x++, y);
		y++;
	}
	return (NULL);
}

void	trace_rays(t_app *app, int scene_id)
{
	int				tr_count;
	t_thread_data	*tr_data;
	int 			tr_id;

	tr_count = 8;
	tr_data = (t_thread_data *)malloc(sizeof(t_thread_data) * tr_count);
	tr_id = 0;
	while (tr_id < tr_count)
	{
		tr_data[tr_id].app = app;
		tr_data[tr_id].scene_id = scene_id;
		tr_data[tr_id].sx = 0;
		tr_data[tr_id].ex = WIDTH;
		tr_data[tr_id].sy = tr_id * (HEIGHT / tr_count);
		tr_data[tr_id].ey = (tr_id + 1) * (HEIGHT / tr_count);
		pthread_create(&tr_data->tr, NULL, init_thread, &tr_data[tr_id++]);
	}
	tr_id = 0;
	while (tr_id < tr_count)
	{
		pthread_join(tr_data[tr_id].tr, NULL);
		tr_id++;
	}
	free(tr_data);
}
