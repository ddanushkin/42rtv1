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

	float speed = 0.1f;
	t_vec	*position;

	position = &app->scene->obj->position;
	position = &app->scene->light->position;

	if (keys[SDL_SCANCODE_W])
		position->z += speed;
	if (keys[SDL_SCANCODE_S])
		position->z -= speed;

	if (keys[SDL_SCANCODE_A])
		position->x += speed;
	if (keys[SDL_SCANCODE_D])
		position->x -= speed;

	if (keys[SDL_SCANCODE_LSHIFT])
		position->y += speed;
	if (keys[SDL_SCANCODE_SPACE])
		position->y -= speed;
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

	oc = vec_sub(ray.origin, center);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0f * vec_dot(oc, ray.direction);
	c = vec_dot(oc, oc) - radius * radius;

	discriminant = b * b - 4 * a * c;

	intersect.t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	intersect.t2 = (-b - sqrtf(discriminant)) / (2.0f * a);
	return (intersect);
}

float	light_intersect(t_ray ray, t_sphere sphere, float min_d, float max_d)
{
	float	distance;
	float	dist_to_sphere;

	distance = max_d;
	if ((dist_to_sphere = hit_sphere(sphere.position, sphere.radius, ray).t1) > -1.0f)
	{
		if ((min_d <= dist_to_sphere) && (dist_to_sphere < distance))
			distance = dist_to_sphere;
	}
	return distance;
}

void	fill_screen(t_app *app)
{
	int			x;
	int			y;
	SDL_Surface *screen;
	t_scene		*scene;
	t_color		c;

	t_ray r;
	r.origin.x = 0.0f;
	r.origin.y = 0.0f;
	r.origin.z = 0.0f;

	float u_scale = 1.0f;
	float v_scale = 1.0f;

	if (WIDTH > HEIGHT)
		u_scale = (float)WIDTH / (float)HEIGHT;
	else if (HEIGHT > WIDTH)
		v_scale = (float)HEIGHT / (float)WIDTH;

	scene = app->scene;

	screen = app->sdl->surface;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r.direction.x = 2.0f * ((float)x / (WIDTH - 1)) - 1.0f;
			r.direction.y = 1.0f - 2.0f * ((float)y / (HEIGHT - 1));
			r.direction.x *= u_scale;
			r.direction.y *= v_scale;

			r.direction.z = 1.0f;

			t_inter_dot		intersect;
			t_sphere		*sphere;

			sphere = scene->obj;
			intersect = hit_sphere(sphere->position, sphere->radius, r);

			if (intersect.t1 > -1.0f)
			{
				t_vec	hit_point = vec_point_at(r.origin, r.direction, intersect.t1);
				t_vec	normal = vec_normalize(vec_sub(sphere->position, hit_point));
				t_vec	hit_p_to_light = vec_sub(scene->light->position, hit_point);
				float	distance_to_light = vec_length(hit_p_to_light);
				t_ray	light_ray;

				light_ray.origin = hit_point;
				light_ray.direction = hit_p_to_light;

				t_color color;
				color = scene->obj->color;

				float distance_to_obstacle = light_intersect(light_ray, *scene->obj, 0, 1000);
				if (distance_to_obstacle < 1000)
				{
					float factor;
					float dot;

					dot = vec_dot(light_ray.direction, normal);
					factor = 128 * MAX(0, dot) * scene->light->intensity / (distance_to_light * distance_to_light);

					color.r = CLAMP(color.r + factor, 0 , 255);
					color.g = CLAMP(color.g + factor, 0 , 255);
					color.b = CLAMP(color.b + factor, 0 , 255);
				}
				set_pixel(screen, x, y, color);
			}

			x++;
		}
		y++;
	}
}

void	set_camera(t_camera *camera, t_vec pos, t_vec look_at)
{
	t_vec		diff_btw;
	t_vec		x_axis;
	t_vec		y_axis;
	t_vec		z_axis;

	x_axis = vec_new(1.0f, 0.0f, 0.0f);
	y_axis = vec_new(0.0f, 1.0f, 0.0f);
	z_axis = vec_new(0.0f, 0.0f, 1.0f);
	camera->pos = pos;
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
	/* Scene */
	app->scene = (t_scene *)malloc(sizeof(t_scene) * 1);

	/* Sphere */
	app->scene->obj = (t_sphere *)malloc(sizeof(t_sphere) * 1);
	app->scene->obj[0].position = vec_new(0.0f, 0.0f, 2.0f);
	app->scene->obj[0].radius = 1.0f;
	set_color(&app->scene->obj->color, 100, 0, 0);

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