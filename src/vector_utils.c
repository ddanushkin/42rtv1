#include "rt.h"

float 	vec_length(t_vec v)
{
	return (sqrtf(vec_dot(v, v)));
}

t_vec	vec_normalize(t_vec v)
{
	t_vec	new_v;
	float	length;

	length = vec_length(v);
	new_v.x = v.x / length;
	new_v.y = v.y / length;
	new_v.z = v.z / length;
	return (new_v);
}

float	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x +
			v1.y * v2.y +
			v1.z * v2.z);
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	new_v;

	new_v.x = v1.y * v2.z - v1.z * v2.y;
	new_v.y = v1.z * v2.x - v1.x * v2.z;
	new_v.z = v1.x * v2.y - v1.y * v2.x;
	return (new_v);
}

t_vec	vec_invert(t_vec v)
{
	t_vec	new_v;

	new_v.x = -v.x;
	new_v.y = -v.y;
	new_v.z = -v.z;
	return (new_v);
}
