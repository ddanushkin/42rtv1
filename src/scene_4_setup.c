#include "rt.h"



void	init_scene_4(t_app *app)
{
	int		*c;
	t_scene	*scene;

	scene = &app->scenes[4];
	c = &scene->counts[0];
	ft_memset(&scene->counts, 0, sizeof(int[5]));
	scene_add_cylinders(scene, 8);
	scene_add_lights(scene, 3);
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(-10, 0, -10),
			vec_new(0, 0, 0),
			5,
			mat_new(1, 0, 10, PINK));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(10, 0, -10),
			vec_new(0, 0, 0),
			5,
			mat_new(1, 0, 10, PINK));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(10, -5, -1),
			vec_new(0, 0, 90),
			1,
			mat_new(1, 0, 10, CYAN));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(10, 5, -1),
			vec_new(0, 0, 90),
			1,
			mat_new(1, 0, 10, CYAN));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(0, 0, -2),
			vec_new(0, 0, 45),
			0.2,
			mat_new(1, 0, 10, RED));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(0, 0, -3),
			vec_new(0, 0, -45),
			0.2,
			mat_new(1, 0, 10, GREEN));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(0, 0, -4),
			vec_new(0, 0, 0),
			0.2,
			mat_new(1, 0, 10, BLUE));

	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.0, 3.0, 10.0),
			100);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(2, 0, -2.0),
			100);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.5, -2.0, 10.0),
			1000);
}