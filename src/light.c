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
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	light_dir = vec_normalize(vec_sub(light.position, hit->p));
	shadow_ray.origin = vec_add(hit->p, vec_mul_by(hit->n, 0.1));
	shadow_ray.direction = light_dir;
	shadow_hit.d = INFINITY;
	shadow_hit.collided = FALSE;
	//check_spheres(scene, shadow_ray, &shadow_hit);
	check_cylinder(scene, shadow_ray, &shadow_hit);
	if (!shadow_hit.collided)
	{
		hit->diffuse += MAX(0.0, vec_dot(light_dir, hit->n))
						* light.intensity;
		hit->specular += pow(MAX(0.0,
			vec_dot(vec_invert(reflect(vec_invert(light_dir), hit->n)),
			ray.direction)), hit->m.exp) * light.intensity;
	}
}

void	process_lights(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	t_light		light;
	t_color		tmp;

	i = 0;
	hit->diffuse = 0;
	hit->specular = 0;
	while (i < scene.counts[COUNT_LIGHT])
	{
		if (i == 3)
		{
			i++;
			continue;
		}
		light = scene.light[i];
		calculate_light(scene, light, hit, ray);
		i++;
	}
	hit->m.c = color_mul_by(hit->m.c, hit->diffuse);
	hit->m.c = color_mul_by(hit->m.c, hit->m.a0);
	tmp = color_mul_by(color_new(255, 255, 255), hit->specular * hit->m.a1);
	hit->m.c = color_sum(hit->m.c, tmp);
	color_clamp(&hit->m.c);
}