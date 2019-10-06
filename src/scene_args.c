#include "rt.h"

void	check_scene_args(t_app *app, int argc, char *argv[])
{
	int scene_id;

	/* TODO: Check max min id of scene */
	app->scene_id = 0;
	if (argc >= 2)
	{
		scene_id = ft_atoi(argv[1]);
		app->scene_id = ft_atoi(argv[1]);
	}
}