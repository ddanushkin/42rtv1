#include "rt.h"

t_vec	vector_new(float x, float y, float z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1;
	return (v);
}

t_vec	vector_add(t_vec vector1, t_vec vector2)
{
	t_vec	result;

	result.x = vector1.x + vector2.x;
	result.y = vector1.y + vector2.y;
	result.z = vector1.z + vector2.z;
	return	result;
}

t_vec	vector_sub(t_vec vector1, t_vec vector2)
{
	t_vec	result;

	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return	result;
}

t_vec	vector_mul_by(t_vec v, float k)
{
	t_vec	result;

	result.x = v.x * k;
	result.y = v.y * k;
	result.z = v.z * k;
	return	(result);
}

t_vec	vector_div_by(t_vec v, float k)
{
	t_vec	result;

	result.x = v.x / k;
	result.y = v.y / k;
	result.z = v.z / k;
	return	(result);
}

void		set_vector(t_vec *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

float 		vector_length(t_vec v)
{
	return (sqrtf(vector_dot_product(v, v)));
}

t_vec	vector_normalise(t_vec v)
{
	t_vec	result;
	float		length;

	length = vector_length(v);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}

float		vector_dot_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x +
			v1.y * v2.y +
			v1.z * v2.z);
}

t_vec	vector_cross_product(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}