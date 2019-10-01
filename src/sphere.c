#include "rt.h"

t_sphere	sphere_new(t_vec pos, float radius, t_color color)
{
	t_sphere	sphere;

	sphere.position = pos;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

float 	select_t(float a, float c)
{
	float	t1;
	float 	t2;

	t1 = a - c;
	t2 = a + c;
	if(t1 < 0.0f)
		t1 = t2;
	if(t1 < 0.0f)
		return INFINITY;
	return (t1);
}

float	sphere_intersection(t_vec center, float radius, t_ray ray)
{
	t_vec	co;
	float	a;
	float	b;
	float	c;

	co = vec_sub(center, ray.origin);
	a = vec_dot(co, ray.direction);
	b = vec_dot(co, co) - a * a;
	if (b > radius * radius)
		return INFINITY;
	c = sqrtf(radius * radius - b);
	return (select_t(a, c));
}

t_vec	sphere_normal(t_vec center, t_vec p)
{
	return (vec_normalize(vec_sub(p, center)));
}