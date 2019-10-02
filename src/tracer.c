#include "rt.h"

void	hit_objects(t_scene scene, t_ray ray, t_hit *hit)
{
	hit->d = INFINITY;
	hit->collided = FALSE;
	check_planes(scene, ray, hit);
	//check_spheres(scene, ray, hit);
	check_cylinder(scene, ray, hit);
	check_cone(scene, ray, hit);
}

void	trace_rays(t_app *app, int scene_id)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;

	ray.origin = app->scene[scene_id].camera.position;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.direction = ray_direction(app, x, y);
			hit_objects(app->scene[scene_id], ray, &hit);
			if (hit.collided)
			{
				process_lights(app->scene[scene_id], ray, &hit);
				set_pixel(app->sdl->surface, x, y, hit.m.c);
			}
			else
				set_pixel(app->sdl->surface, x, y, BLACK);
			x++;
		}
		y++;
	}
}
