#include <rt.h>

int		event_handling(t_app *app)
{
	const uint8_t	*keys;

	keys = app->keys;
	SDL_WaitEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return(0);
	if (keys[SDL_SCANCODE_ESCAPE])
		return(0);
	event_move(keys, &app->pos);
	event_rotate(keys, &app->rot);
	event_change_scene(app, keys);
	event_redraw(app, keys);
	return (1);
}

int		render_loop(t_app *app)
{
	trace_rays(app);
	SDL_UpdateWindowSurface(app->sdl->window);
	while (1)
	{
		if (!event_handling(app))
			break;
	}
	return (0);
}

void	safe_quit(t_app *app)
{
	SDL_Quit();
	exit(0);
}

int		main(int argc, char *argv[])
{
    t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	args_check_pos(app, argc, argv);
	args_check_rot(app, argc, argv);
    init_sdl(app);
	init_app(app);
	init_scenes(app);
	render_loop(app);
	safe_quit(app);
    return (0);
}