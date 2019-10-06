#include "rt.h"

void	set_app_position(t_app *app, int x, int y, int z)
{
	app->pos = vec_new(x, y, z);
}

void	set_app_rotation(t_app *app, int x, int y, int z)
{
	app->rot = vec_new(x, y, z);
}

void	check_pos_args(t_app *app, int argc, char *argv[])
{
	/* TODO: Check max min position */
	set_app_position(app, 0, 0, 5);
	if (argc == 5)
		set_app_position(
				app,
				ft_atoi(argv[1]),
				ft_atoi(argv[2]),
				ft_atoi(argv[3]));
}

void	check_rot_args(t_app *app, int argc, char *argv[])
{
	/* TODO: Check max min rotation */
	set_app_rotation(app, 0, 0, 0);
	if (argc == 8)
		set_app_rotation(
				app,
				ft_atoi(argv[1]),
				ft_atoi(argv[2]),
				ft_atoi(argv[3]));
}