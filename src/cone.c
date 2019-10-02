#include "rt.h"

t_cone	cone_new(t_vec pos, double radius, double height, t_material material)
{
	t_cone	cone_new;

	cone_new.position = pos;
	cone_new.radius = radius;
	cone_new.height = height;
	cone_new.mat = material;

	return (cone_new);
}


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

double	cone_intersection(t_cone cone, t_ray ray)
{
	double	A = ray.origin.x - cone.position.x;
	double	B = ray.origin.z - cone.position.z;
	double	D = cone.height - ray.origin.y + cone.position.y;

	double	tan = (cone.radius / cone.height) * (cone.radius / cone.height);

	double	a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z) - (tan * (ray.direction.y * ray.direction.y));
	double	b = (2 * A * ray.direction.x) + (2 * B * ray.direction.z) + (2 * tan * D * ray.direction.y);
	double	c = (A * A) + (B * B) - (tan * (D * D));

	double	delta = b * b - 4 * (a * c);
	if(fabs(delta) < 0.001)
		return INFINITY;
	if(delta < 0.0)
		return INFINITY;

	return (select_t(a, b, delta));
//	double	t1 = (-b - sqrt(delta)) / (2 * a);
//	double	t2 = (-b + sqrt(delta))/(2 * a);

}


t_vec	cone_normal(t_vec p, t_cone	cone)
{
	double	r = sqrt((p.x - cone.position.x) * (p.x - cone.position.x) + (p.z - cone.position.z) * (p.z - cone.position.z));
	t_vec	n = vec_new(p.x - cone.position.x, r * (cone.radius / cone.height), p.z - cone.position.z);
	n = vec_normalize(n);
	return n;
}

void	check_cone(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	double		dist;
	t_cone		cone;

	i = 0;
	while (i < scene.counts[COUNT_SPHERE])
	{
		cone = scene.cones[i];
		dist = cone_intersection(cone, ray);
		if (dist < hit->d)
		{
			hit->m = cone.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray.origin, ray.direction, dist);
			hit->n = cone_normal(hit->p, cone);
			hit->collided = TRUE;
		}
		i++;
	}
//	float r = pos.y + t*dir.y;
//
//	if ((r > center.y) and (r < center.y + height)) return t;
//	else return -1;
}