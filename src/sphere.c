#include "rt.h"

t_sphere		sphere_new(t_vec pos, double rad, t_material mat)
{
	t_sphere	sphere;

	sphere.pos = pos;
	sphere.rad = rad;
	sphere.mat = mat;
	return (sphere);
}

double			sphere_intersection(t_ray ray, t_sphere sphere)
{
	t_vec	co;
	double	a;
	double	b;
	double	c;

	co = vec_sub(ray.o, sphere.pos);
	a = vec_dot(ray.d, ray.d);
	b = vec_dot(ray.d, co) * 2.0;
	c = vec_dot(co, co) - sphere.rad * sphere.rad;
	return (calc_abc(a, b, c));
}

t_vec			sphere_normal(t_vec p, t_vec center)
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
		dist = sphere_intersection(ray, sphere);
		if (dist < hit->d)
		{
			hit->m = sphere.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray, dist);
			hit->n = sphere_normal(hit->p, sphere.pos);
			hit->collided = TRUE;
		}
		i++;
	}
}
