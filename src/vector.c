#include "rt.h"

t_vec	vec_new(double x, double y, double z)
{
	t_vec	new_v;

	new_v.x = x;
	new_v.y = y;
	new_v.z = z;
	return (new_v);
}

t_vec	vec_point_at(t_ray ray, double length)
{
	return (vec_add(ray.o, vec_mul_by(ray.d, length)));
}
