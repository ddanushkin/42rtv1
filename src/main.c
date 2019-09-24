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

	if (keys[SDL_SCANCODE_W])
		app->obj[0].pos.z -= 1.01f;
	if (keys[SDL_SCANCODE_S])
		app->obj[0].pos.z += 1.01f;

	if (keys[SDL_SCANCODE_A])
		app->obj[0].pos.x -= 1.01f;
	if (keys[SDL_SCANCODE_D])
		app->obj[0].pos.x += 1.01f;
	return (1);
}

t_inter_dot		hit_sphere(t_vec center, float radius, t_ray ray)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_inter_dot		intersect;

	oc = vec_sub(ray.o, center);
	a = vec_dot(ray.d, ray.d);
	b = 2.0f * vec_dot(oc, ray.d);
	c = vec_dot(oc, oc) - radius * radius;

	discriminant = b * b - 4 * a * c;

	intersect.t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	intersect.t2 = (-b - sqrtf(discriminant)) / (2.0f * a);
	return (intersect);
}

void	fill_screen(t_app *app)
{
	int			x;
	int			y;
	SDL_Surface *screen;
	t_color		c;

	t_ray r;
	r.o.x = 0.0f;
	r.o.y = 0.0f;
	r.o.z = -1000.0f;

	screen = app->sdl->surface;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r.d.x = (float)x * (1.0f / (float)WIDTH) - 0.5f;
			r.d.y = (float)y * (1.0f / (float)HEIGHT) - 0.5f;
			r.d.z = 1.0f;

			t_inter_dot		intersect;
			intersect = hit_sphere(app->obj[0].pos, app->obj[0].radius, r);
			x++;
		}
		y++;
	}
}

void	set_camera(t_app *app)
{
	t_camera	*camera;
	t_vec		look_at;
	t_vec		diff_btw;

	/* TODO: Move to struct app->xyz */
	t_vec x_axis;
	t_vec y_axis;
	t_vec z_axis;
	x_axis = vec_new(1.0f, 0.0f, 0.0f);
	y_axis = vec_new(0.0f, 1.0f, 0.0f);
	z_axis = vec_new(0.0f, 0.0f, 1.0f);

	camera = &app->camera;
	camera->pos = vec_new(0, 0, -5.0f);
	look_at = vec_new(0.0f, 0.0f, 0.0f);
	diff_btw = vec_new(
			camera->pos.x - look_at.x,
			camera->pos.y - look_at.y,
			camera->pos.z - look_at.z);
	camera->dir = vec_normalize(vec_invert(diff_btw));
	camera->right = vec_normalize(vec_cross(y_axis, camera->dir));
	camera->down = vec_cross(camera->right, camera->dir);
}

int		render_loop(t_app *app)
{
	app->obj = (t_sphere *)malloc(sizeof(t_sphere) * 1);
	app->obj[0].pos.x = 0.0f;
	app->obj[0].pos.y = 0.0f;
	app->obj[0].pos.z = 0.0f;
	app->obj[0].radius = 420.0f;

	set_camera(app);

	while (1)
	{
		clear_screen(app);
		if (!event_handling(app))
			break;

		//fill_screen(app);

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