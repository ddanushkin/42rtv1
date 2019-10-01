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
	int		*counts;
	t_scene	*scene;

	/* Scene */
	app->scene = (t_scene *)malloc(sizeof(t_scene) * 1);
	scene = &app->scene[0];

	counts = &scene->counts[0];
	counts[COUNT_SPHERE] = 6;
	counts[COUNT_PLANES] = 2;
	counts[COUNT_CONE] = 1;
	counts[COUNT_CYLINDER] = 1;
	counts[COUNT_LIGHT] = 4;

	/* Planes */
	scene->planes = (t_plane *)malloc(sizeof(t_plane) * counts[COUNT_PLANES]);
	scene->planes[0] = plane_new(
			vec_new(0.0f, 0.0f, -10.0f),
			vec_new(0.0f, 0.0f, -1.0f),
			material_new(0.1f, 0.1f, BLUE));
	scene->planes[1] = plane_new(
			vec_new(0.0f, -1.0f, 0.0f),
			vec_new(0.0f, -1.0f, 0.0f),
			material_new(0.1f, 0.1f, GREY));

	/* Sphere */
	scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * counts[COUNT_SPHERE]);
	scene->spheres[0] = sphere_new(
			vec_new(-0.0f, -0.2f, -3.2f), 0.4f,
			material_new(0.8f, 0.1f, RED));
	scene->spheres[1] = sphere_new(
			vec_new(0, 0.0f, -4.0f), 1.0f,
			material_new(0.8f, 0.8f, BROWN));
	scene->spheres[2] = sphere_new(
			vec_new(0.3f, 0.2f, -3.2f), 0.3f,
			material_new(0.5f, 0.5f, WHITE));
	scene->spheres[3] = sphere_new(
			vec_new(-0.3f, 0.2f, -3.2f), 0.3f,
			material_new(0.5f, 0.5f, WHITE));
	scene->spheres[4] = sphere_new(
			vec_new(0.3f, 0.2f, -2.9f), 0.1f,
			material_new(0.1f, 0.1f, BLACK));
	scene->spheres[5] = sphere_new(
			vec_new(-0.3f, 0.2f, -2.9f), 0.1f,
			material_new(0.1f, 0.1f, BLACK));

	/* Light */
	scene->light = (t_light *)malloc(sizeof(t_light) * counts[COUNT_LIGHT]);
	scene->light[0] = light_new(vec_new(10.0f, 1.0f, -3.0f), 0.5f);
	scene->light[1] = light_new(vec_new(-10.0f, 1.0f, -3.0f), 0.5f);
	scene->light[2] = light_new(vec_new(0.0f, 10.0f, -3.0f), 1.0f);
	scene->light[3] = light_new(vec_new(0.0f, 0.0f, 5.0f), 1.0f);

	/* Camera */
	set_camera(
			&scene->camera,
			vec_new(0.0f, 0.0f, 0.0f),
			vec_new(0.0f, 0.0f, 0.0f));

	app->rot = vec_new(0.0f, 0.0f, 0.0f);
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

int		main(int argc, char *argv[])
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