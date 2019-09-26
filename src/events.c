#include "rt.h"

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

	//position = &app->scene->obj->position;
	//position = &app->scene->light->position;
	position = &app->scene->camera.position;

	if (keys[SDL_SCANCODE_W])
		position->z -= speed;
	if (keys[SDL_SCANCODE_S])
		position->z += speed;
	if (keys[SDL_SCANCODE_A])
		position->x -= speed;
	if (keys[SDL_SCANCODE_D])
		position->x += speed;
	if (keys[SDL_SCANCODE_LSHIFT])
		position->y -= speed;
	if (keys[SDL_SCANCODE_SPACE])
		position->y += speed;
	return (1);
}