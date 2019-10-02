#include "rt.h"

t_sphere		sphere_new(t_vec pos, double radius, t_material mat)
{
	t_sphere	sphere;

	sphere.position = pos;
	sphere.radius = radius;
	sphere.mat = mat;
	return (sphere);
}

static double	select_t(double a, double c)
{
	double	t1;
	double 	t2;

	t1 = a - c;
	t2 = a + c;
	if(t1 < 0.0)
		t1 = t2;
	if(t1 < 0.0)
		return INFINITY;
	return (t1);
}

double			sphere_intersection(t_vec center, double radius, t_ray ray)
{
	t_vec	co;
	double	a;
	double	b;
	double	c;

	co = vec_sub(center, ray.origin);
	a = vec_dot(co, ray.direction);
	b = vec_dot(co, co) - a * a;
	if (b > radius * radius)
		return INFINITY;
	c = sqrt(radius * radius - b);
	return (select_t(a, c));
}

t_vec			sphere_normal(t_vec center, t_vec p)
{
	return (vec_normalize(vec_sub(p, center)));
}

void			check_spheres(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	double		dist;
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
