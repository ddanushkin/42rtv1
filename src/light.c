#include "rt.h"

t_vec	reflect(t_vec i, t_vec n)
{
	return (vec_sub(i, vec_mul_by(n, 2.0 * vec_dot(i, n))));
}

t_light	light_new(t_vec position, double intensity)
{
	t_light light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

void	calculate_light(t_scene scene, t_light light, t_hit *hit, t_ray ray)
{
	t_vec	light_dir;
	double	light_dist;
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	light_dir = vec_normalize(vec_sub(light.position, hit->p));
	light_dist = sqrt(
			pow((light.position.x - hit->p.x), 2.0) +
			pow((light.position.y - hit->p.y), 2.0) +
			pow((light.position.z - hit->p.z), 2.0)) ;
	shadow_ray.o = vec_add(hit->p, vec_mul_by(hit->n, 0.1));
	shadow_ray.d = light_dir;
	shadow_hit.d = INFINITY;
	shadow_hit.collided = FALSE;
	check_spheres(scene, shadow_ray, &shadow_hit);
	check_cylinder(scene, shadow_ray, &shadow_hit);
	check_cone(scene, shadow_ray, &shadow_hit);
	if (!shadow_hit.collided || shadow_hit.d > light_dist)
	{
		light.intensity /= 4.0 * M_PI * pow(light_dist, 2.0);
		hit->diffuse += MAX(0.0, vec_dot(light_dir, hit->n))
						* light.intensity;
		hit->specular += pow(MAX(0.0,
			vec_dot(vec_invert(reflect(vec_invert(light_dir), hit->n)),
			ray.d)), hit->m.exp) * light.intensity;
	}
}

void	process_lights(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	t_light		light;
	t_color		tmp;

	i = 0;
	hit->diffuse = 0.1;
	hit->specular = 0.0;
	while (i < scene.counts[LIGHT_OBJ])
	{
		light = scene.lights[i];
		calculate_light(scene, light, hit, ray);
		i++;
	}
	hit->m.c = color_mul_by(hit->m.c, hit->diffuse * hit->m.a0);
	tmp = color_mul_by(WHITE, hit->specular * hit->m.a1);
	hit->m.c = color_sum(hit->m.c, tmp);
	color_clamp(&hit->m.c);
}