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

typedef struct	s_ray
{
	t_vec		o;
	t_vec		d;
}				t_ray;

typedef struct s_inter_dot
{
	float		t1;
	float		t2;
}				t_inter_dot;

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
	t_sphere	*obj;
}				t_app;

void	set_pixel(SDL_Surface *surface, int x, int y, t_color c);
t_color	get_pixel(SDL_Surface *surface, int x, int y);

float 		vector_length(t_vec v);
t_vec	vector_normalise(t_vec v);
float		vector_dot_product(t_vec v1, t_vec v2);
t_vec	vector_cross_product(t_vec v1, t_vec v2);
t_vec	vector_add(t_vec vector1, t_vec vector2);
t_vec	vector_new(float x, float y, float z);
t_vec	vector_sub(t_vec vector1, t_vec vector2);
t_vec	vector_mul_by(t_vec v, float k);
t_vec	vector_div_by(t_vec v, float k);

#endif
