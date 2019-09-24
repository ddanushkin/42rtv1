#include <rt.h>

int init_sdl(t_app *app)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	app->sdl->window = SDL_CreateWindow(SDL_WINDOW_ARGS);
	app->sdl->surface = SDL_GetWindowSurface(app->sdl->window);
	return (0);
}

void	clear_screen(t_app *app)
{
	ft_memset(app->sdl->surface->pixels, 0, SURFACE_LEN);
}

int		event_handling(t_app *app)
{
	const uint8_t *keys;

	keys = app->keys;
	SDL_PollEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return(0);
	if (keys[SDL_SCANCODE_ESCAPE])
		return(0);
	return (1);
}

void	fill_screen(t_app *app)
{
	int			x;
	int			y;
	SDL_Surface *screen;
	t_color		c;

	screen = app->sdl->surface;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.r = rand() % 256;
			c.g = rand() % 256;
			c.b = rand() % 256;
			set_pixel(screen, x, y, c);
			x++;
		}
		y++;
	}
}

int		render_loop(t_app *app)
{
	while (1)
	{
		clear_screen(app);
		if (!event_handling(app))
			break;

		fill_screen(app);

		SDL_UpdateWindowSurface(app->sdl->window);
	}
	return (0);
}

void	safe_quit(t_app *app)
{
	SDL_Quit();
	if (app->sdl)
		free(app->sdl);
	free(app);
}

int		main()
{
    t_app *app;

    app = (t_app *)malloc(sizeof(t_app));
    app->sdl = (t_sdl *)malloc(sizeof(t_sdl));

    init_sdl(app);

	app->keys = SDL_GetKeyboardState(NULL);

	render_loop(app);
	safe_quit(app);
    return 0;
}