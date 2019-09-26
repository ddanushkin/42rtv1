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
	float denom = vec_dot(normal, ray.direction);
	float t;

	t = -1.0f;
	if (denom > 1e-6f)
	{
		t_vec p0l0 = vec_sub(pos,ray.origin);
		t = vec_dot(p0l0, normal) / denom;
		return (t >= 0 ? t : -1.0f);
	}
	return (-1.0f);
}