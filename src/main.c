/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:15:03 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/09 20:44:02 by lglover          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		event_handling(t_app *app)
{
	const uint8_t	*keys;

	keys = app->keys;
	SDL_WaitEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return (0);
	if (keys[SDL_SCANCODE_ESCAPE])
		return (0);
	event_move(keys, &app->pos);
	event_rotate(keys, &app->rot);
	event_redraw(app, keys);
	return (1);
}

int		render_loop(t_app *app)
{
	trace_rays(app);
	SDL_UpdateWindowSurface(app->sdl->window);
	while (1)
	{
		if (!event_handling(app))
			break ;
	}
	return (0);
}

void	safe_quit(t_app *app, char *status)
{
	ft_putendl(status);
	SDL_FreeSurface(app->sdl->surface);
	SDL_DestroyWindow(app->sdl->window);
	SDL_Quit();
	exit(0);
}

int		main(int argc, char *argv[])
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	init_sdl(app);
	init_app(app);
	if (argc == 1)
		read_config(app, "scenes/0.scene");
	else
		read_config(app, argv[1]);
	render_loop(app);
	safe_quit(app, STATUS_OK);
	return (0);
}
