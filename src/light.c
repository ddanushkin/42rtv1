#include "rt.h"

t_vec	reflect(t_vec i, t_vec n)
{
	return (vec_sub(i, vec_mul_by(n, 2.0 * vec_dot(i, n))));
}

t_light	light_new(t_vec position, t_color color, double intensity)
{
	t_light light;

	light.position = position;
	light.intensity = intensity;
	light.mat.c = color;
	return (light);
}

t_color	blend_color(t_color c1, t_color c2)
{
	t_color c;
	t_color w;
	double br;

	w.r = MIN(c1.r, MIN(c1.g, c1.b));
	w.g = MIN(c2.r, MIN(c2.g, c2.b));
	w.b = (w.r + w.g) / 2;
	c1.r -= w.r;
	c1.g -= w.r;
	c1.b -= w.r;
	c2.r -= w.g;
	c2.g -= w.g;
	c2.b -= w.g;
	br = (MAX(c1.r, MAX(c1.g, c1.b)) + MAX(c2.r, MAX(c2.g, c2.b)))
			/ (2.0 * 255.0);
	c.r = (c1.r + c2.r) * br + w.b;
	c.g = (c1.g + c2.g) * br + w.b;
	c.b = (c1.b + c2.b) * br + w.b;
	return (c);
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