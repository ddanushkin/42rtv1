#ifndef RT_H
#define RT_H

# include "libft.h"
# include <stdio.h> /* TODO: Delete before finish project */
# include <SDL.h>

# define TITLE "RTV1"
# define WIDTH 720
# define HEIGHT 720
# define ASP_RATIO (float)WIDTH / (float)HEIGHT
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
	t_vec		origin;
	t_vec		direction;
	t_vec		point_at;
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
	t_vec		position;
	float		radius;
	t_color		color;
}				t_sphere;

typedef struct	s_light
{
	t_vec		position;
	float		intensity;
	t_color		color;
}				t_light;

typedef struct	s_camera
{
	t_vec		pos;
	t_vec		dir;
	t_vec		right;
	t_vec		down;
}				t_camera;

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	SDL_Event	event;
}				t_sdl;

typedef struct	s_scene
{
	t_sphere	*obj;
	t_light		*light;
	t_camera	camera;
}				t_scene;

typedef struct	s_app
{
	t_sdl		*sdl;
	const Uint8	*keys;
	t_scene		*scene;
}				t_app;

void	set_pixel(SDL_Surface *surface, int x, int y, t_color c);
t_color	get_pixel(SDL_Surface *surface, int x, int y);

float 	vec_length(t_vec v);
t_vec	vec_normalize(t_vec v);
float	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_new(float x, float y, float z);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mul_by(t_vec v, float k);
t_vec	vec_div_by(t_vec v, float k);
t_vec	vec_invert(t_vec v);
t_vec	vec_point_at(t_vec ori, t_vec dir, float t);

void	set_color(t_color *c, int r, int g, int b);

#endif
