#include "rt.h"

t_vec	vec_new(double x, double y, double z)
{
	t_vec	new_v;

	new_v.x = x;
	new_v.y = y;
	new_v.z = z;
	return (new_v);
}

t_vec	vec_point_at(t_vec ori, t_vec dir, double t)
{
	return (vec_add(ori, vec_mul_by(dir, t)));
}
