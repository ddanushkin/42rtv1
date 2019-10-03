#include "rt.h"

void	event_redraw(t_app *app, const uint8_t *keys)
{
	if (keys[SDL_SCANCODE_W]
	|| keys[SDL_SCANCODE_A]
	|| keys[SDL_SCANCODE_S]
	|| keys[SDL_SCANCODE_D]
	|| keys[SDL_SCANCODE_LSHIFT]
	|| keys[SDL_SCANCODE_RSHIFT]
	|| keys[SDL_SCANCODE_SPACE]
	|| keys[SDL_SCANCODE_LEFT]
	|| keys[SDL_SCANCODE_RIGHT]
	|| keys[SDL_SCANCODE_UP]
	|| keys[SDL_SCANCODE_DOWN])
		app->redraw = TRUE;
}

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

	keys = app->keys;
	SDL_WaitEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return(0);
	if (keys[SDL_SCANCODE_ESCAPE])
		return(0);
	event_move(keys, &app->pos, 0.1);
	event_rotate(keys, &app->rot, 0.1);
	event_redraw(app, keys);
	return (1);
}