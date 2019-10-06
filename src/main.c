#include <rt.h>

int init_sdl(t_app *app)
{
	app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	SDL_Init(SDL_INIT_EVERYTHING);
	app->sdl->window = SDL_CreateWindow(WINDOW_CONFIG);
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
	int		*c;
	t_scene	*scene;

	/* Scene */
	app->scene = (t_scene *)malloc(sizeof(t_scene) * 1);
	scene = &app->scene[0];

	c = &scene->counts[0];
	c[SPHERE_OBJ] = 3;
	c[PLANE_OBJ] = 2;
	c[CONE_OBJ] = 2;
	c[CYLINDER_OBJ] = 2;
	c[LIGHT_OBJ] = 4;

	/* Scene malloc */
	scene->planes = (t_plane *)malloc(sizeof(t_plane) * c[PLANE_OBJ]);
	scene->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * c[CYLINDER_OBJ]);
	scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * c[SPHERE_OBJ]);
	scene->cones = (t_cone *)malloc((sizeof(t_cone) * c[CONE_OBJ]));
	scene->light = (t_light *)malloc(sizeof(t_light) * c[LIGHT_OBJ]);

	/* Reset counts */
	c[SPHERE_OBJ] = 0;
	c[PLANE_OBJ] = 0;
	c[CONE_OBJ] = 0;
	c[CYLINDER_OBJ] = 0;
	c[LIGHT_OBJ] = 0;

	/* Planes */
	t_plane *plane;

	plane = &scene->planes[c[PLANE_OBJ]];
	*plane = plane_new(
			vec_new(0.0, -3.0, 0.0),
			vec_new(0.0, 0.0, 0.0),
			mat_new(0.8, 0.8, 10, WHITE));
	c[PLANE_OBJ]++;

	plane = &scene->planes[c[PLANE_OBJ]];
	*plane = plane_new(
			vec_new(0.0, 0.0, -10.0),
			vec_new(90.0, 0.0, 0.0),
			mat_new(0.8, 0.8, 10, WHITE));
	c[PLANE_OBJ]++;

	/* Cylinder */
	t_cylinder *cylinder;

	cylinder = &scene->cylinders[c[CYLINDER_OBJ]];
	*cylinder = cylinder_new(
			vec_new(3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			0.2,
			mat_new(0.8, 0.8, 15, ORANGE));
	c[CYLINDER_OBJ]++;

	cylinder = &scene->cylinders[c[CYLINDER_OBJ]];
	*cylinder = cylinder_new(
			vec_new(-3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			0.2,
			mat_new(0.8, 0.8, 15, ORANGE));
	c[CYLINDER_OBJ]++;

	/*Cone*/
	t_cone *cone;

	cone = &scene->cones[c[CONE_OBJ]];
	*cone = cone_new(
			vec_new(3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			40.0,
			mat_new(0.8, 0.8, 150, GREY));
	c[CONE_OBJ]++;

	cone = &scene->cones[c[CONE_OBJ]];
	*cone = cone_new(
			vec_new(-3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			40.0,
			mat_new(0.8, 0.8, 150, GREY));
	c[CONE_OBJ]++;

	/* Sphere */
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(-1.2, 0.0, 0.0),
			0.5,
			mat_new(0.8, 1.8, 150, RED));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(0.0, 0.0, 0.0),
			0.6,
			mat_new(0.8, 1.8, 150, GREEN));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(1.2, 0.0, 0.0),
			0.5,
			mat_new(0.8, 1.8, 150, BLUE));

	/* Light */
	scene->light[c[LIGHT_OBJ]++] = light_new(
			vec_new(-1.2, 0.0, 5.0),
			100);
	scene->light[c[LIGHT_OBJ]++] = light_new(
			vec_new(1.2, 0.0, 5.0),
			100);
	scene->light[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.0, 5.0, 10.0),
			100);

	app->redraw = TRUE;
}

int		render_loop(t_app *app)
{
	trace_rays(app, 0);
	SDL_UpdateWindowSurface(app->sdl->window);
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

    if (argc == 1)
    {
		print_usage();
		exit(0);
    }
	app = (t_app *)malloc(sizeof(t_app));
	check_pos_args(app, argc, argv);
	check_rot_args(app, argc, argv);
    init_sdl(app);
	init_app(app);
	init_scene(app);
	render_loop(app);
	safe_quit(app);
    return (0);
}