#include "rt.h"

t_material	material_new(double albedo_0, double albedo_1, double exp, t_color color)
{
	t_material mat;

	mat.a0 = albedo_0;
	mat.a1 = albedo_1;
	mat.c = color;
	mat.exp = exp;
	return (mat);
}