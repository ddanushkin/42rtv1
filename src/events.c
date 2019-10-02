#include "rt.h"

void 	event_move(const uint8_t *keys, t_vec *pos, double speed)
{
	if (keys[SDL_SCANCODE_W])
		pos->z -= speed;
	if (keys[SDL_SCANCODE_S])
		pos->z += speed;
	if (keys[SDL_SCANCODE_A])
		pos->x -= speed;
	if (keys[SDL_SCANCODE_D])
		pos->x += speed;
	if (keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT])
		pos->y -= speed;
	if (keys[SDL_SCANCODE_SPACE])
		pos->y += speed;
}

void 	event_rotate(const uint8_t *keys, t_vec *rot, double speed)
{
	if (keys[SDL_SCANCODE_LEFT])
		rot->y -= speed;
	if (keys[SDL_SCANCODE_RIGHT])
		rot->y += speed;
	if (keys[SDL_SCANCODE_UP])
		rot->x += speed;
	if (keys[SDL_SCANCODE_DOWN])
		rot->x -= speed;
}

int		event_handling(t_app *app)
{
	const uint8_t	*keys;
	t_vec			*position;
	t_vec			*rotation;

	keys = app->keys;
	SDL_WaitEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return(0);
	if (keys[SDL_SCANCODE_ESCAPE])
		return(0);
	position = &app->scene->camera.position;
	rotation = &app->rot;
	event_move(keys, position, 0.1);
	event_rotate(keys, rotation, 0.1);
	return (1);
}