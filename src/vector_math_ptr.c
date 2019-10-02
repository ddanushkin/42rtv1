#include "rt.h"

void	vec_add_ptr(t_vec *ov, t_vec v2)
{
	ov->x += v2.x;
	ov->y += v2.y;
	ov->z += v2.z;
}

void	vec_sub_ptr(t_vec *ov, t_vec v2)
{
	ov->x -= v2.x;
	ov->y -= v2.y;
	ov->z -= v2.z;
}

void	vec_mul_by_ptr(t_vec *ov, double k)
{
	ov->x *= k;
	ov->y *= k;
	ov->z *= k;
}

void	vec_div_by_ptr(t_vec *ov, double k)
{
	ov->x /= k;
	ov->y /= k;
	ov->z /= k;
}
