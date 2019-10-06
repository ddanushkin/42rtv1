#include "rt.h"

t_vec	ray_direction(t_app *app, int x, int y)
{
	t_vec v;
	t_vec tmp;
	double angle;

	angle = tanf(M_PI * 0.5 * app->fov / 180.0);
	v.x = 2.0 * ((double)x / (WIDTH - 1)) - 1.0;
	v.y = 1.0 - 2.0 * ((double)y / (HEIGHT - 1));
	v.x *= angle * app->asp_rat;
	v.y *= angle;
	v.z = -1.0;
	set_view(&v, app->rot);
	return (v);
}