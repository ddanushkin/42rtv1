#include "rt.h"

void	color_set(t_color *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

t_color	color_new(int r, int g, int b)
{
	t_color new_c;
	new_c.r = r;
	new_c.g = g;
	new_c.b = b;
	return (new_c);
}