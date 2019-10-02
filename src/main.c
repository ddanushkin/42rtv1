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
	app->fov = 90.0;
	app->asp_rat = (double)WIDTH / (double)HEIGHT;
}

void	init_scene(t_app *app)
{
	int		*counts;
	t_scene	*scene;

	/* Scene */
	app->scene = (t_scene *)malloc(sizeof(t_scene) * 1);
	scene = &app->scene[0];

	counts = &scene->counts[0];
	counts[COUNT_SPHERE] = 3;
	counts[COUNT_PLANES] = 2;
	counts[COUNT_CONE] = 1;
	counts[COUNT_CYLINDER] = 1;
	counts[COUNT_LIGHT] = 4;

	/* Planes */
	scene->planes = (t_plane *)malloc(sizeof(t_plane) * counts[COUNT_PLANES]);
	scene->planes[0] = plane_new(
			vec_new(0.0, 0.0, -7.0),
			vec_new(0.0, 0.0, -1.0),
			material_new(0.8, 0.8, 10, WHITE));
	scene->planes[1] = plane_new(
			vec_new(0.0, -1.0, 0.0),
			vec_new(0.0, -1.0, 0.0),
			material_new(0.8, 0.8, 10, WHITE));

	/* Cylinder */
	scene->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * counts[COUNT_CYLINDER]);
	scene->cylinders[0] = cylinder_new(
			vec_new(0.0, 0.0, -3.5), 0.5,
			material_new(0.8, 0.8, 15, BROWN));

	/* Sphere */
	scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * counts[COUNT_SPHERE]);
	scene->spheres[0] = sphere_new(
			vec_new(-1.2, 0.0, -3.0), 0.5,
			material_new(0.8, 1.8, 150, RED));
	scene->spheres[1] = sphere_new(
			vec_new(1.2, 0.0, -3.0), 0.5,
			material_new(0.8, 0.2, 150, BROWN));
	scene->spheres[2] = sphere_new(
			vec_new(0.0, 0.0, -3.0), 0.5,
			material_new(0.8, 0.2, 150, WHITE));

	/*Cone*/
	scene->cones = (t_cone *)malloc((sizeof(t_cone) * counts[COUNT_CONE]));
	scene->cones[0] = cone_new(
			vec_new(0, 0, -3.0f), 1.0f, 2.0f,
			material_new(0.8f, 0.8f, 150, WHITE));

	/* Light */
	scene->light = (t_light *)malloc(sizeof(t_light) * counts[COUNT_LIGHT]);
	scene->light[0] = light_new(vec_new(10.0, 1.0, -3.0), 0.5);
	scene->light[1] = light_new(vec_new(-10.0, 1.0, -3.0), 0.5);
	scene->light[2] = light_new(vec_new(0.0, 10.0, -1.0), 1.0);
	scene->light[3] = light_new(vec_new(0.0, 0.0, 5.0), 1.0);

	/* Camera */
	set_camera(
			&scene->camera,
			vec_new(0.0, 0.0, 0.0),
			vec_new(0.0, 0.0, 0.0));

	app->rot = vec_new(0.0, 0.0, 0.0);
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