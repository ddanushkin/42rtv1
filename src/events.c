/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:11:40 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:13:05 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	event_redraw(t_app *app, const uint8_t *keys)
{
	if (keys[SDL_SCANCODE_W] ||
	keys[SDL_SCANCODE_A] ||
	keys[SDL_SCANCODE_S] ||
	keys[SDL_SCANCODE_D] ||
	keys[SDL_SCANCODE_LSHIFT] ||
	keys[SDL_SCANCODE_RSHIFT] ||
	keys[SDL_SCANCODE_SPACE] ||
	keys[SDL_SCANCODE_LEFT] ||
	keys[SDL_SCANCODE_RIGHT] ||
	keys[SDL_SCANCODE_UP] ||
	keys[SDL_SCANCODE_DOWN] ||
	keys[SDL_SCANCODE_1] ||
	keys[SDL_SCANCODE_2] ||
	keys[SDL_SCANCODE_3] ||
	keys[SDL_SCANCODE_4] ||
	keys[SDL_SCANCODE_0])
	{
		trace_rays(app);
		SDL_UpdateWindowSurface(app->sdl->window);
	}
}

void	event_move(const uint8_t *keys, t_vec *pos)
{
	if (keys[SDL_SCANCODE_W])
		pos->z -= POS_SPEED;
	if (keys[SDL_SCANCODE_S])
		pos->z += POS_SPEED;
	if (keys[SDL_SCANCODE_A])
		pos->x -= POS_SPEED;
	if (keys[SDL_SCANCODE_D])
		pos->x += POS_SPEED;
	if (keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT])
		pos->y -= POS_SPEED;
	if (keys[SDL_SCANCODE_SPACE])
		pos->y += POS_SPEED;
}

void	event_rotate(const uint8_t *keys, t_vec *rot)
{
	if (keys[SDL_SCANCODE_LEFT])
		rot->y -= ROT_SPEED;
	if (keys[SDL_SCANCODE_RIGHT])
		rot->y += ROT_SPEED;
	if (keys[SDL_SCANCODE_UP])
		rot->x += ROT_SPEED;
	if (keys[SDL_SCANCODE_DOWN])
		rot->x -= ROT_SPEED;
}
