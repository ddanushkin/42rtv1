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

	/* Scene malloc */
	scene->planes = (t_plane *)malloc(sizeof(t_plane) * counts[COUNT_PLANES]);
	scene->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * counts[COUNT_CYLINDER]);
	scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * counts[COUNT_SPHERE]);
	scene->cones = (t_cone *)malloc((sizeof(t_cone) * counts[COUNT_CONE]));
	scene->light = (t_light *)malloc(sizeof(t_light) * counts[COUNT_LIGHT]);

	/* Reset counts */
	counts[COUNT_SPHERE] = 0;
	counts[COUNT_PLANES] = 0;
	counts[COUNT_CONE] = 0;
	counts[COUNT_CYLINDER] = 0;
	counts[COUNT_LIGHT] = 0;

	/* Planes */
	scene->planes[counts[COUNT_PLANES]] = plane_new(
			vec_new(0.0, -10.0, 0.0),
			vec_new(0.0, 0.0, 45.0),
			mat_new(0.8, 0.8, 10, WHITE));
	set_axis(
			&scene->planes[counts[COUNT_PLANES]].axis,
			scene->planes[counts[COUNT_PLANES]].rot);
	counts[COUNT_PLANES]++;

	scene->planes[counts[COUNT_PLANES]] = plane_new(
			vec_new(0.0, -10.0, 0.0),
			vec_new(0.0, 0.0, -45.0),
			mat_new(0.8, 0.8, 10, WHITE));
	set_axis(
			&scene->planes[counts[COUNT_PLANES]].axis,
			scene->planes[counts[COUNT_PLANES]].rot);
	counts[COUNT_PLANES]++;

	/* Cylinder */
	scene->cylinders[counts[COUNT_CYLINDER]] = cylinder_new(
			vec_new(0.0, 2.0, -5.5),
			vec_new(0.0, 0.0, -25.0),
			0.5,
			mat_new(0.8, 0.8, 15, PINK));
	set_axis(
			&scene->cylinders[counts[COUNT_CYLINDER]].axis,
			scene->cylinders[counts[COUNT_CYLINDER]].rot);
	counts[COUNT_CYLINDER]++;

	/*Cone*/
	scene->cones[counts[COUNT_CONE]] = cone_new(
			vec_new(0.0, 1.0, -5.0),
			vec_new(0.0, 0.0, 25.0),
			10.0,
			mat_new(0.8, 0.8, 150, GREEN));
	set_axis(
			&scene->cones[counts[COUNT_CONE]].axis,
			scene->cones[counts[COUNT_CONE]].rot);
	counts[COUNT_CONE]++;

	/* Sphere */
	scene->spheres[counts[COUNT_SPHERE]++] = sphere_new(
			vec_new(-1.2, 0.0, -3.0),
			0.5,
			mat_new(0.8, 1.8, 150, RED));
	scene->spheres[counts[COUNT_SPHERE]++] = sphere_new(
			vec_new(0.0, 0.0, -3.0),
			0.6,
			mat_new(0.4, 0.4, 100, WHITE));
	scene->spheres[counts[COUNT_SPHERE]++] = sphere_new(
			vec_new(1.2, 0.0, -3.0),
			0.5,
			mat_new(0.8, 0.1, 10, BROWN));

	/* Light */
	scene->light[counts[COUNT_LIGHT]++] = light_new(
			vec_new(5.0, 0.0, 0.0),
			color_new(255, 0, 0),
			500.0);
	scene->light[counts[COUNT_LIGHT]++] = light_new(
			vec_new(-5.0, 0.0, 0.0),
			color_new(0, 0, 255),
			300.0);
//	scene->light[counts[COUNT_LIGHT]++] = light_new(
//			vec_new(0.0, 3.0, 0.0),
//			color_new(255, 255, 0),
//			100.0);

	app->pos = vec_new(0.0, 0.0, 2.0);
	app->rot = vec_new(0.0, 0.0, 0.0);
	app->redraw = TRUE;
}

int		render_loop(t_app *app)
{
	while (1)
	{
		if (!event_handling(app))
			break;
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