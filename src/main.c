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
	//ft_memset(app->sdl->surface->pixels, 0, SURFACE_LEN);
}

void	fill_screen(t_app *app)
{
	int			x;
	int			y;
	SDL_Surface *screen;
	t_scene		*scene;

	t_ray r;
	r.origin = app->scene->camera.position;

	float u_scale;
	float v_scale;

	u_scale = WIDTH > HEIGHT ? (float)WIDTH / (float)HEIGHT : 1.0f;
	v_scale = HEIGHT > WIDTH ? (float)HEIGHT / (float)WIDTH : 1.0f;

	scene = app->scene;
	screen = app->sdl->surface;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r.direction.x = ((float)x / (WIDTH - 1)) - 0.5f;
			r.direction.y = 0.5f - ((float)y / (HEIGHT - 1));
			r.direction.x *= u_scale;
			r.direction.y *= v_scale;
			r.direction.z = 1.0f;

			float			intersect;
			t_sphere		*sphere;

			sphere = scene->obj;
			intersect = sphere_intersection(sphere->position, sphere->radius, r);
			if (intersect > 0.0f)
			{
				t_vec	hit_point = vec_point_at(r.origin, r.direction, intersect);
				t_vec	normal = sphere_normal(sphere->position, hit_point);
				t_vec	hit_p_to_light = vec_sub(scene->light->position, hit_point);
				float	distance_to_light = vec_length(hit_p_to_light);
				t_ray	light_ray;

				light_ray.origin = hit_point;
				light_ray.direction = hit_p_to_light;

				t_color color;
				color = scene->obj->color;

				float distance_to_obstacle = sphere_intersection(sphere->position, sphere->radius, r);
				if (distance_to_obstacle > 0.0f)
				{
					float factor;
					float dot;

					dot = vec_dot(light_ray.direction, normal);
					factor = 128 * MAX(0, dot) * scene->light->intensity / (distance_to_light * distance_to_light);

					color.r = CLAMP(color.r + factor, 0, 255);
					color.g = CLAMP(color.g + factor, 0, 255);
					color.b = CLAMP(color.b + factor, 0, 255);
				}
				set_pixel(screen, x, y, color);
			}
			else
				set_pixel(screen, x, y, BLACK);
			x++;
		}
		y++;
	}
}

int		render_loop(t_app *app)
{
	/* Scene */
	app->scene = (t_scene *)malloc(sizeof(t_scene) * 1);

	/* Sphere */
	app->scene->obj = (t_sphere *)malloc(sizeof(t_sphere) * 1);
	app->scene->obj[0].position = vec_new(0.0f, 0.0f, 4.0f);
	app->scene->obj[0].radius = 1.0f;
	app->scene->obj->color = GREY;

	/* Light */
	app->scene->light = (t_light *)malloc(sizeof(t_light) * 1);
	app->scene->light->position = vec_new(0.0f, 0.0f, -5.0f);
	app->scene->light->intensity = 15.0f;

	/* Camera */
	set_camera(
			&app->scene->camera,
			vec_new(0.0f, 0.0f, 0.0f),
			vec_new(0.0f, 0.0f, 0.0f));

	while (1)
	{
		//clear_screen(app);
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