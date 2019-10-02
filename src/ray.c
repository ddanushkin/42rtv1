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

	tmp = v;
	tmp.y = v.y * cos(app->rot.x) - v.z * sin(app->rot.x);
	tmp.z = v.y * sin(app->rot.x) + v.z * cos(app->rot.x);
	v = tmp;
	tmp.x = v.x * cos(app->rot.y) - v.z * sin(app->rot.y);
	tmp.z = v.x * sin(app->rot.y) + v.z * cos(app->rot.y);
	v = vec_normalize(tmp);
	return (v);
}