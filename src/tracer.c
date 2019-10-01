#include "rt.h"

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
			hit->color = sphere.color;
			hit->d = dist;
			hit->p = vec_point_at(ray.origin, ray.direction, dist);
			hit->n = sphere_normal(sphere.position, hit->p);
			hit->collided = TRUE;
		}
		i++;
	}
}


t_vec	plane_normal(t_vec plane, t_ray ray)
{
	t_vec result = vec_cross(vec_sub(ray.direction, plane), vec_sub(ray.origin, plane));

	return (vec_normalize(result));
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
			hit->color = plane.color;
			hit->d = dist;
			hit->p = vec_point_at(ray.origin, ray.direction, dist);
			hit->n = plane_normal(plane.normal, ray);
			hit->collided = TRUE;
		}
		i++;
	}
}

float	norm(t_vec vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec	reflect(t_vec I, t_vec N)
{
	return vec_sub(I, vec_mul_by(N, 2.0f * vec_dot(I, N)));
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
				/* Light */
				float	diffuse = 0;
				float	specular = 0;
				t_vec	light_dir	= vec_normalize(vec_sub(app->scene[scene_id].light[0].position, ray.origin));

				float	light_dist = norm(vec_sub(app->scene[scene_id].light->position, ray.origin));
				t_vec	shadow_orig = vec_dot(light_dir, hit.n) ? vec_sub(ray.origin, vec_mul_by(hit.n, 1e-3f)) : vec_add(hit.n, vec_mul_by(hit.n, 1e-3f));

				float	light_intensity = app->scene[scene_id].light[0].intensity;
				diffuse += MAX(0.0f, vec_dot(light_dir, hit.n)) * light_intensity;

				specular += powf(MAX(0.0f,vec_dot(vec_invert(reflect(vec_invert(light_dir), hit.n)), ray.direction)),10.0f) * light_intensity;

				float albedo_0 = 0.6f;
				float albedo_1 = 0.3f;
				t_color tmp;
				hit.color = color_mul_by(hit.color, diffuse);
				hit.color = color_mul_by(hit.color, albedo_0);
				tmp = color_mul_by(color_new(255, 255, 255), specular * albedo_1);
				hit.color = color_sum(hit.color, tmp);
				color_clamp(&hit.color);
				set_pixel(app->sdl->surface, x, y, hit.color);
			}
			else
				set_pixel(app->sdl->surface, x, y, BLACK);
			x++;
		}
		y++;
	}
}