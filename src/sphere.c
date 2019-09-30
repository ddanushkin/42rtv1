#include "rt.h"

t_sphere	sphere_new(t_vec pos, float radius, t_color color)
{
	t_sphere sphere;

	sphere.position = pos;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

float 	select_t(float a, float b, float d)
{
	float	t1;
	float 	t2;
	float 	a2;

	a2 = 2.0f * a;
	t1 = (-b + sqrtf(d)) / a2;
	t2 = (-b - sqrtf(d)) / a2;
	if(fabsf(t1) < 0.001f)
	{
		if (t2 > 0.0f)
			return t2;
		else
			t1 = INFINITY;
	}
	if(fabsf(t2) < 0.001f)
		t2 = INFINITY;
	return (t1 < t2) ? t1 : t2;
}

float	sphere_intersection(t_vec center, float radius, t_ray ray)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;

	oc = vec_sub(ray.origin, center);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0f * vec_dot(oc, ray.direction);
	c = vec_dot(oc, oc) - radius * radius;
	return (select_t(a, b, b * b - 4 * a * c));
}

t_vec	sphere_normal(t_vec center, t_vec p)
{
	return (vec_normalize(vec_sub(p, center)));
}