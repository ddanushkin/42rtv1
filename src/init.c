/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:04:42 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:04:56 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_app(t_app *app)
{
	app->keys = SDL_GetKeyboardState(NULL);
	app->fov = 90.0;
	app->asp_rat = (double)WIDTH / (double)HEIGHT;
	app->redraw = TRUE;
	app->scenes = (t_scene *)malloc(sizeof(t_scene) * 10);
	app->scene_id = 0;
}

int		init_sdl(t_app *app)
{
	app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	SDL_Init(SDL_INIT_EVERYTHING);
	app->sdl->window = SDL_CreateWindow(
			TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			0);
	app->sdl->surface = SDL_GetWindowSurface(app->sdl->window);
	return (0);
}

void	init_scenes(t_app *app)
{
	init_scene_0(app);
	init_scene_1(app);
	init_scene_2(app);
	init_scene_3(app);
	init_scene_4(app);
}
