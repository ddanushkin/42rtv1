#include "rt.h"

t_cone	cone_new(t_vec pos, t_vec rot, double angle, t_material material)
{
	t_cone	cone;

	cone.pos = pos;
	cone.rot = rot;
	cone.angle = angle * M_PI / 180.0;
	cone.mat = material;
	return (cone);
}

double	cone_intersection(t_ray ray, t_cone obj)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double 	k;

	oc = vec_sub(ray.o, obj.pos);
	k = tan(obj.angle);
	k = 1.0 + k * k;
	a = vec_dot(ray.d, ray.d) - k * pow(vec_dot(ray.d, obj.axis), 2);
	b = (vec_dot(ray.d, oc) - k * vec_dot(ray.d, obj.axis) * vec_dot(oc, obj.axis)) * 2.0;
	c = vec_dot(oc, oc) - k * pow(vec_dot(oc, obj.axis), 2);
	return (calc_abc(a, b, c));
}

t_vec	cone_normal(t_ray ray, t_hit hit, t_cone obj)
{
	t_vec	oc;
	t_vec	n;
	double	m;
	double	k;

	oc = vec_sub(ray.o, obj.pos);
	k = tan(obj.angle);
	k = 1.0 + k * k;
	m = vec_dot(ray.d, obj.axis) * hit.d + vec_dot(oc, obj.axis);
	n = vec_sub(
			vec_sub(hit.p, obj.pos),
			vec_mul_by(vec_mul_by(obj.axis, m), k));
	return vec_normalize(n);
}

void	check_cone(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	double		dist;
	t_cone		cone;

	i = 0;
	while (i < scene.counts[COUNT_CONE])
	{
		cone = scene.cones[i];
		dist = cone_intersection(ray, cone);
		if (dist < hit->d)
		{
			hit->m = cone.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray, dist);
			hit->n = cone_normal(ray, *hit, cone);
			hit->collided = TRUE;
		}
		i++;
	}
}