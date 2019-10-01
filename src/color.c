#include "rt.h"

t_color	color_new(int r, int g, int b)
{
	t_color new_c;
	new_c.r = r;
	new_c.g = g;
	new_c.b = b;
	return (new_c);
}

void	color_clamp(t_color *c)
{
	c->r = CLAMP(c->r, 0, 255);
	c->g = CLAMP(c->g, 0, 255);
	c->b = CLAMP(c->b, 0, 255);
}

t_color	color_sum(t_color c1, t_color c2)
{
	t_color	new_c;
	new_c.r = c1.r + c2.r;
	new_c.g = c1.g + c2.g;
	new_c.b = c1.b + c2.b;
	return (new_c);
}

t_color color_add(t_color c, float k)
{
	t_color new_c;

	new_c.r = c.r + k;
	new_c.g = c.g + k;
	new_c.b = c.b + k;
	return (new_c);
}

t_color	color_mul(t_color c1, t_color c2)
{
	t_color	new_c;
	new_c.r = c1.r * c2.r / 255;
	new_c.g = c1.g * c2.g / 255;
	new_c.b = c1.b * c2.b / 255;
	return (new_c);
}

t_color	color_mul_by(t_color c, float k)
{
	t_color new_c;

	new_c.r = c.r * k;
	new_c.g = c.g * k;
	new_c.b = c.b * k;
	return (new_c);
}

int		color_channel_mix(int channel_a, int channel_b, float amount)
{
	return ((int)(((float)channel_a * amount) +
			((float)channel_b * (1.0f - amount))));
}

t_color color_mix(t_color c1, t_color c2, float amount)
{
	t_color new_c;

	new_c.r = color_channel_mix(c2.r, c1.r, amount);
	new_c.g = color_channel_mix(c2.g, c1.g, amount);
	new_c.b = color_channel_mix(c2.b, c1.b, amount);
	return (new_c);
}