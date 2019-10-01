#include "rt.h"

t_vec	ray_direction(t_app *app, int x, int y)
{
	t_vec v;
	t_vec tmp;
	float angle;

	angle = tanf(M_PI * 0.5f * app->fov / 180.0f);
	v.x = 2.0f * ((float)x / (WIDTH - 1)) - 1.0f;
	v.y = 1.0f - 2.0f * ((float)y / (HEIGHT - 1));
	v.x *= angle * app->asp_rat;
	v.y *= angle;
	v.z = -1.0f;

	tmp = v;
	tmp.y = v.y * cosf(app->rot.x) - v.z * sinf(app->rot.x);
	tmp.z = v.y * sinf(app->rot.x) + v.z * cosf(app->rot.x);
	v = tmp;
	tmp.x = v.x * cosf(app->rot.y) - v.z * sinf(app->rot.y);
	tmp.z = v.x * sinf(app->rot.y) + v.z * cosf(app->rot.y);
	v = vec_normalize(tmp);
	return (v);
}