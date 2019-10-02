#include "rt.h"

void	set_camera(t_camera *camera, t_vec pos, t_vec look_at)
{
	t_vec		diff_btw;
	t_vec		x_axis;
	t_vec		y_axis;
	t_vec		z_axis;

	x_axis = vec_new(1.0, 0.0, 0.0);
	y_axis = vec_new(0.0, 1.0, 0.0);
	z_axis = vec_new(0.0, 0.0, 1.0);
	camera->position = pos;
	diff_btw = vec_new(
			camera->position.x - look_at.x,
			camera->position.y - look_at.y,
			camera->position.z - look_at.z);
	camera->dir = vec_normalize(vec_invert(diff_btw));
	camera->right = vec_normalize(vec_cross(y_axis, camera->dir));
	camera->down = vec_cross(camera->right, camera->dir);
}