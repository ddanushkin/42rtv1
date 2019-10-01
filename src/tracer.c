#include "rt.h"

t_vec	reflect(t_vec I, t_vec N)
{
	return vec_sub(I, vec_mul_by(N, 2.0f * vec_dot(I, N)));
}

void	check_spheres(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	float		dist;
	t_sphere	sphere;

	i = 0;
	while (i < scene.counts[COUNT_SPHERE])
	{
		sphere = scene.spheres[i];
		dist = sphere_intersection(sphere.position, sphere.radius, ray);
		if (dist < hit->d)
		{
			hit->m = sphere.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray.origin, ray.direction, dist);
			hit->n = sphere_normal(sphere.position, hit->p);
			hit->collided = TRUE;
		}
		i++;
	}
}

void	check_planes(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	float		dist;
	t_plane		plane;

	i = 0;
	while (i < scene.counts[COUNT_PLANES])
	{
		plane = scene.planes[i];
		dist = plane_intersection(ray, plane.position, plane.normal);
		if (dist < hit->d)
		{
			hit->m = plane.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray.origin, ray.direction, dist);
			hit->n = vec_invert(plane.normal);
			hit->collided = TRUE;
		}
		i++;
	}
}

void	process_lights(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	t_light		light;
	float		diffuse;
	float		specular;

	i = 0; /* TODO: Set to 0 */
	diffuse = 0;
	specular = 0;
	while (i < scene.counts[COUNT_LIGHT])
	{
		t_vec	light_dir;

		light = scene.light[i];
		light_dir = vec_normalize(vec_sub(light.position, hit->p));

		t_ray	shadow_ray;
		t_hit	shadow_hit;

		shadow_ray.origin = vec_add(hit->p, vec_mul_by(hit->n, 0.1f));
		shadow_ray.direction = light_dir;

		/* Reset hit struct */
		shadow_hit.d = INFINITY;
		shadow_hit.collided = FALSE;

		/* Check light_ray collision with objects */
		check_spheres(scene, shadow_ray, &shadow_hit);

		if (shadow_hit.collided)
		{
			diffuse += MAX(0.0f, vec_dot(light_dir, hit->n)) * 0.0f;
			specular += powf(MAX(0.0f,vec_dot(vec_invert(reflect(vec_invert(light_dir), hit->n)), ray.direction)),10.0f) * 0.0f;
		}
		else
		{
			diffuse += MAX(0.0f, vec_dot(light_dir, hit->n)) * light.intensity;
			specular += powf(MAX(0.0f,vec_dot(vec_invert(reflect(vec_invert(light_dir), hit->n)), ray.direction)),10.0f) * light.intensity;
		}
		i++;
	}
	t_color	tmp;

	hit->m.c = color_mul_by(hit->m.c, diffuse);
	hit->m.c = color_mul_by(hit->m.c, hit->m.a0);
	tmp = color_mul_by(color_new(255, 255, 255), specular * hit->m.a1);
	hit->m.c = color_sum(hit->m.c, tmp);
	color_clamp(&hit->m.c);
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

			/* Reset hit struct */
			hit.d = INFINITY;
			hit.collided = FALSE;

			/* Check ray collision with objects */
			check_planes(app->scene[scene_id], ray, &hit);
			check_spheres(app->scene[scene_id], ray, &hit);

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