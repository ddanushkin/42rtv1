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

typedef struct	s_color
{
	int 	r;
	int 	g;
	int 	b;
	int 	a;
}				t_color;

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec;

typedef struct	s_mat4x4
{
	float		m[4][4];
}				t_mat4x4;

typedef struct	s_sphere
{
	t_vec		pos;
	float		radius;
	t_color		color;
}				t_sphere;

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	SDL_Event	event;
}				t_sdl;

typedef struct	s_app
{
	t_sdl		*sdl;
	const Uint8	*keys;
}				t_app;

void	set_pixel(SDL_Surface *surface, int x, int y, t_color c);
t_color	get_pixel(SDL_Surface *surface, int x, int y);

#endif
