#include "rt.h"

t_cylinder		cylinder_new(t_vec pos, t_vec rot, double rad, t_material mat)
{
	t_cylinder cylinder;

	cylinder.pos = pos;
	cylinder.rot = rot;
	cylinder.rad = rad;
	cylinder.mat = mat;
	return (cylinder);
}

double			cylinder_intersection(t_ray ray, t_cylinder	obj)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;

	oc = vec_sub(ray.o, obj.pos);
	a   = vec_dot(ray.d , ray.d)
			- pow(vec_dot(ray.d, obj.axis), 2);
	b = (vec_dot(ray.d, oc)
			- vec_dot(ray.d, obj.axis) * vec_dot(oc, obj.axis)) * 2;
	c   = vec_dot(oc, oc)
			- pow(vec_dot(oc , obj.axis), 2) - obj.rad * obj.rad;
	return (calc_abc(a, b, c));
}

t_vec			cylinder_normal(t_ray ray, t_hit hit, t_cylinder obj)
{
	t_vec	oc;
	t_vec	n;
	double	m;

	oc = vec_sub(ray.o, obj.pos);
	m = vec_dot(ray.d, obj.axis) * hit.d + vec_dot(oc, obj.axis);
	n = vec_sub(vec_sub(hit.p, obj.pos), vec_mul_by(obj.axis, m));
	return (vec_normalize(n));
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
		dist = cylinder_intersection(ray, cylinder);
		if (dist < hit->d)
		{
			hit->m = cylinder.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray, dist);
			hit->n = cylinder_normal(ray, *hit, cylinder);
			hit->collided = TRUE;
		}
		i++;
	}
}
