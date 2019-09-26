#include "rt.h"

t_hit	check_spheres(t_scene scene, t_ray ray)
{
	int			i;
	t_hit		hit;
	float		dist;
	float 		min_dist;
	t_sphere	sphere;

	i = 0;
	dist = INFINITY;
	min_dist = INFINITY;
	hit.d = -1.0f;
	while (i < scene.counts[COUNT_SPHERE])
	{
		sphere = scene.spheres[i];
		dist = sphere_intersection(sphere.position, sphere.radius, ray);
		if (dist <= min_dist)
		{
			hit.color = sphere.color;
			hit.p = vec_point_at(ray.origin, ray.direction, dist);
			hit.n = sphere_normal(sphere.position, hit.p);
			hit.d = dist;
			min_dist = dist;
		}
		i++;
	}
	return (hit);
}

t_hit	check_planes(t_scene scene, t_ray ray)
{
	int			i;
	t_hit		hit;
	float		dist;
	float 		min_dist;
	t_plane		plane;

	i = 0;
	dist = INFINITY;
	min_dist = INFINITY;
	hit.d = -1.0f;
	while (i < scene.counts[COUNT_PLANES])
	{
		plane = scene.planes[i];
		dist = plane_intersection(ray, plane.position, plane.normal);
		if (dist <= min_dist)
		{
			hit.color = plane.color;
			hit.p = vec_point_at(ray.origin, ray.direction, dist);
			hit.n = plane.normal;
			hit.d = dist;
			min_dist = dist;
		}
		i++;
	}
	return (hit);
}

t_hit	choose_hit(t_hit hits[4])
{
	int		i;
	int 	near_i;
	float	min_dist;
	float 	dist;

	i = 0;
	dist = INFINITY;
	min_dist = INFINITY;
	near_i = 0;
	while (i < 4)
	{
		dist = hits[i].d;
		if (dist <= min_dist)
		{
			near_i = i;
			min_dist = dist;
		}
		i++;
	}
	return (hits[near_i]);
}

void	set_infinity_hits(t_hit *hits)
{
	hits[0].d = INFINITY;
	hits[1].d = INFINITY;
	hits[2].d = INFINITY;
	hits[3].d = INFINITY;
}

void	trace_rays(t_app *app, int scene_id)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hits[4];
	t_hit	nearest_hit;

	set_infinity_hits(&hits[0]);
	ray.origin = app->scene[scene_id].camera.position;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.direction = ray_direction(app, x, y);
			hits[COUNT_PLANES] = check_planes(app->scene[scene_id], ray);
			//hits[COUNT_SPHERE] = check_spheres(app->scene[scene_id], ray);
			nearest_hit = choose_hit(hits);
			if (nearest_hit.d > 0.00001f)
				set_pixel(app->sdl->surface, x, y, nearest_hit.color);
			else
				set_pixel(app->sdl->surface, x, y, BLACK);
			x++;
		}
		y++;
	}
}