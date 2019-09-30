#include <rt.h>

int init_sdl(t_app *app)
{
	app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	SDL_Init(SDL_INIT_EVERYTHING);
	app->sdl->window = SDL_CreateWindow(SDL_WINDOW_ARGS);
	app->sdl->surface = SDL_GetWindowSurface(app->sdl->window);
	return (0);
}

void	safe_quit(t_app *app)
{
	SDL_Quit();
	if (app->sdl)
		free(app->sdl);
	free(app);
}

void	init_app(t_app *app)
{
	app->keys = SDL_GetKeyboardState(NULL);
	app->fov = 90.0f;
	app->asp_rat = (float)WIDTH / (float)HEIGHT;
}

void	init_scene(t_app *app)
{
	/* Scene */
	app->scene = (t_scene *)malloc(sizeof(t_scene) * 1);

	app->scene->counts[COUNT_SPHERE] = 2;
	app->scene->counts[COUNT_PLANES] = 2;
	app->scene->counts[COUNT_CONE] = 1;
	app->scene->counts[COUNT_CYLINDER] = 1;

	app->scene->planes = (t_plane *)malloc(sizeof(t_plane) * app->scene->counts[COUNT_PLANES]);
	app->scene->planes[0] = plane_new(vec_new(0, 0, -3.5f), vec_new(1, 0, -1.0f), BLUE);
	app->scene->planes[1] = plane_new(vec_new(0, -1, 0), vec_new(0, -1, 0), GREY);
	/* Sphere */
	app->scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * app->scene->counts[COUNT_SPHERE]);
	app->scene->spheres[0] = sphere_new(vec_new(0, -0.5f, -4), 1.0f, RED);
	app->scene->spheres[1] = sphere_new(vec_new(-1, 0, -3), 1.0f, GREEN);

	/* Light */
	app->scene->light = (t_light *)malloc(sizeof(t_light) * 1);
	app->scene->light->position = vec_new(0.0f, 0.0f, 5.0f);
	app->scene->light->direction = vec_new(0.0f, -1.0f, 0.0f);
	app->scene->light->color = color_new(255,255,1);
	app->scene->light->intensity = 1.0f;

	/* Camera */
	set_camera(
			&app->scene->camera,
			vec_new(0.0f, 0.0f, 0.0f),
			vec_new(0.0f, 0.0f, 0.0f));
}

int		render_loop(t_app *app)
{
	while (1)
	{
		if (!event_handling(app))
			break;

		trace_rays(app, 0);
		SDL_UpdateWindowSurface(app->sdl->window);
	}
	return (0);
}

int		main()
{
    t_app *app;

    app = (t_app *)malloc(sizeof(t_app));
    init_sdl(app);
	init_app(app);
	init_scene(app);
	render_loop(app);
	safe_quit(app);
    return 0;
}