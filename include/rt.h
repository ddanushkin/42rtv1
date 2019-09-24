#ifndef RT_H
#define RT_H

# include "libft.h"
# include <stdio.h> /* TODO: Delete before finish project */
# include <SDL.h>

# define TITLE "RTV1"
# define WIDTH 500
# define HEIGHT 500
# define HWIDTH ((float)WIDTH*0.5f)
# define HHEIGHT ((float)HEIGHT*0.5f)
# define SDL_WINDOW_ARGS TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0
# define SURFACE_LEN WIDTH * HEIGHT * 4

typedef struct	s_sdl
{
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Event	event;
}				t_sdl;

typedef struct	s_app
{
	t_sdl		*sdl;
	const Uint8	*keys;
}				t_app;

#endif
