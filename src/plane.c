#include "rt.h"

t_plane plane_new(t_vec pos, t_vec normal, t_material mat)
{
	t_plane	plane;

	plane.position = pos;
	plane.normal = normal;
	plane.mat = mat;
	return (plane);
}

double	plane_intersection(t_ray ray, t_vec pos, t_vec normal)
{
	double	denom;
	double	t;

	t = INFINITY;
	denom = vec_dot(ray.direction, normal);
	if (denom > 0.0000001)
		t = vec_dot(normal, vec_sub(pos,ray.origin)) / denom;
	return (t);
}