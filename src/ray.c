#include "rt.h"

t_vec	ray_direction(t_app *app, int x, int y)
{
	t_vec v;
	float angle = tanf(M_PI * 0.5f * app->fov / 180.0f);

	v.x = 2.0f * ((float)x / (WIDTH - 1)) - 1.0f;
	v.y = 1.0f - 2.0f * ((float)y / (HEIGHT - 1));
	v.x *= angle * app->asp_rat;
	v.y *= angle;
	v.z = -1.0f;
	v = vec_normalize(v);

	return (v);
}