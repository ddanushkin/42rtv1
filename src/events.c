#include "rt.h"

int		event_handling(t_app *app)
{
	const uint8_t *keys;

	keys = app->keys;
	SDL_WaitEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return(0);
	if (keys[SDL_SCANCODE_ESCAPE])
		return(0);

	double speed = 0.1;
	t_vec	*position;
	t_vec	*rotation;
//	position = &app->scene->obj->position;
//	position = &app->scene->light->position;
	position = &app->scene->camera.position;
	rotation = &app->rot;
	if (keys[SDL_SCANCODE_W])
		position->z -= speed;
	if (keys[SDL_SCANCODE_S])
		position->z += speed;
	if (keys[SDL_SCANCODE_A] && (position->x > 0 || position->x < WIDTH))
		position->x -= speed;
	if (keys[SDL_SCANCODE_D])
		position->x += speed;
	if (keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT])
		position->y -= speed;
	if (keys[SDL_SCANCODE_SPACE])
		position->y += speed;

	if (keys[SDL_SCANCODE_LEFT])
		rotation->y -= speed;
	if (keys[SDL_SCANCODE_RIGHT])
		rotation->y += speed;
	if (keys[SDL_SCANCODE_UP])
		rotation->x += speed;
	if (keys[SDL_SCANCODE_DOWN])
		rotation->x -= speed;
	return (1);
}