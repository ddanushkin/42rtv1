#ifndef RT_H
#define RT_H

# include "math.h"
# include "libft.h"
# include <stdio.h> /* TODO: Delete before finish project */
# include <SDL.h>

# define TITLE "RTV1"
# define WIDTH 500
# define HEIGHT 500
# define ASP_RATIO (float)WIDTH / (float)HEIGHT
# define HWIDTH ((float)WIDTH*0.5f)
# define HHEIGHT ((float)HEIGHT*0.5f)
# define SDL_WINDOW_ARGS TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0
# define SURFACE_LEN WIDTH * HEIGHT * 4
# define BLACK color_new(0, 0, 0)
# define GREY color_new(128, 128, 128)
# define RED color_new(255, 0, 0)
# define GREEN color_new(0, 255, 0)
# define BLUE color_new(0, 0, 255)

# define COUNT_SPHERE 0
# define COUNT_CONE 1
# define COUNT_PLANES 2
# define COUNT_CYLINDER 3

# define TRUE 1
# define FALSE 0

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

typedef struct	s_hit
{
	t_vec		p;
	t_vec		n;
	float 		d;
	t_color		color;
	int 		collided;
}				t_hit;

typedef struct	s_sphere
{
	t_vec		position;
	float		radius;
	t_color		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vec		position;
	t_vec		normal;
	t_color		color;
}				t_plane;

typedef struct	s_cone
{
	t_vec		position;
	float 		radius;
	float 		height;
	float 		angle;
	t_color		color;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec		position;
	float 		radius;
	float 		height;
	float 		angle;
	t_color		color;
}				t_cylinder;

typedef struct	s_light
{
	t_vec		position;
	t_vec		direction;
	float		intensity;
	t_color		color;
}				t_light;

typedef struct	s_camera
{
	t_vec		position;
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
	t_sphere	*spheres;
	t_sphere	*cones;
	t_plane		*planes;
	t_sphere	*cylinders;
	int 		counts[4];
	t_light		*light;
	t_camera	camera;
}				t_scene;

typedef struct	s_app
{
	t_sdl		*sdl;
	const Uint8	*keys;
	t_scene		*scene;
	float 		fov;
	float 		asp_rat;
}				t_app;

void		set_pixel(SDL_Surface *surface, int x, int y, t_color c);
t_color		get_pixel(SDL_Surface *surface, int x, int y);

float 		vec_length(t_vec v);
t_vec		vec_normalize(t_vec v);
float		vec_dot(t_vec v1, t_vec v2);
t_vec		vec_cross(t_vec v1, t_vec v2);
t_vec		vec_add(t_vec v1, t_vec v2);
t_vec		vec_new(float x, float y, float z);
t_vec		vec_sub(t_vec v1, t_vec v2);
t_vec		vec_mul_by(t_vec v, float k);
t_vec		vec_div_by(t_vec v, float k);
t_vec		vec_invert(t_vec v);
t_vec		vec_point_at(t_vec ori, t_vec dir, float t);

void		color_set(t_color *c, int r, int g, int b);
t_color		color_new(int r, int g, int b);
t_color 	color_plus(t_color c, float k);
t_color		color_mul(t_color c1, t_color c2);
t_color		color_mul_by(t_color c, float k);
t_color		color_mix(t_color c1, t_color c2, float amount);
void		color_clamp(t_color *c);

void		set_camera(t_camera *camera, t_vec pos, t_vec look_at);

t_vec		ray_direction(t_app *app, int x, int y);

int			event_handling(t_app *app);

void		trace_rays(t_app *app, int scene_id);

float		sphere_intersection(t_vec center, float radius, t_ray ray);
t_vec		sphere_normal(t_vec center, t_vec p);
t_sphere	sphere_new(t_vec pos, float radius, t_color color);

float		plane_intersection(t_ray ray, t_vec pos, t_vec normal);
t_plane		plane_new(t_vec pos, t_vec normal, t_color color);
#endif
