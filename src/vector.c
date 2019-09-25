#include "rt.h"

t_vec	vec_new(float x, float y, float z)
{
	t_vec	new_v;

	new_v.x = x;
	new_v.y = y;
	new_v.z = z;
	new_v.w = 1;
	return (new_v);
}

t_vec	vec_point_at(t_vec ori, t_vec dir, float t)
{
	return (vec_add(vec_mul_by(dir, t), ori));
}
