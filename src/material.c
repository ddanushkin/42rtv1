#include "rt.h"

t_material	material_new(float albedo_0, float albedo_1, t_color color)
{
	t_material mat;

	mat.a0 = albedo_0;
	mat.a1 = albedo_1;
	mat.c = color;
	return (mat);
}