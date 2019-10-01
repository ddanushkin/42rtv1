#include "rt.h"

t_plane plane_new(t_vec pos, t_vec normal, t_color color)
{
	t_plane	plane;

	plane.position = pos;
	plane.normal = normal;
	plane.color = color;
	return (plane);
}

float	plane_intersection(t_ray ray, t_vec pos, t_vec normal)
{
	float	denom;
	float	t;

	t = INFINITY;
	denom = vec_dot(ray.direction, normal);
	if (denom > 1e-6f)
		t = vec_dot(normal, vec_sub(pos,ray.origin)) / denom;
	return (t);
}