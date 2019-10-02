#include "rt.h"

static double	select_t(double  a, double b, double d)
{
	double sqrt_delta;
	double t1;
	double t2;

	sqrt_delta = sqrt(d);
	t1 = (-b - sqrt_delta) / (2 * a);
	t2 = (-b + sqrt_delta) / (2 * a);
	if(t1 < 0.0)
		t1 = t2;
	if(t1 < 0.0)
		return INFINITY;
	return (t1);
}

double			cylinder_intersection(t_ray ray, t_vec center, double rad)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = (ray.direction.x * ray.direction.x)
			+ (ray.direction.z * ray.direction.z);
	b = 2 * (ray.direction.x * (ray.origin.x - center.x)
			+ ray.direction.z * (ray.origin.z - center.z));
	c = (ray.origin.x - center.x) * (ray.origin.x - center.x)
			+ (ray.origin.z - center.z) * (ray.origin.z - center.z)
			- (rad * rad);
	delta = b * b - 4 * (a * c);
	if (fabs(delta) < 0.001)
		return INFINITY;
	if (delta < 0.0)
		return INFINITY;
	return (select_t(a, b, delta));
}

t_vec			cylinder_normal(t_vec center, t_vec p)
{
	t_vec	v;

	v = vec_new(p.x - center.x, 0, p.z - center.z);
	return (vec_normalize(v));
}

t_cylinder		cylinder_new(t_vec pos, double radius, t_material mat)
{
	t_cylinder cylinder;

	cylinder.position = pos;
	cylinder.radius = radius;
	cylinder.mat = mat;
	return (cylinder);
}

void			check_cylinder(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	double		dist;
	t_cylinder	cylinder;

	i = 0;
	while (i < scene.counts[COUNT_CYLINDER])
	{
		cylinder = scene.cylinders[i];
		dist = cylinder_intersection(ray, cylinder.position, cylinder.radius);
		if (dist < hit->d)
		{
			hit->m = cylinder.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray.origin, ray.direction, dist);
			hit->n = cylinder_normal(cylinder.position, hit->p);
			hit->collided = TRUE;
		}
		i++;
	}
}
