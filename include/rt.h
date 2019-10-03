#ifndef RT_H
#define RT_H

# include "math.h"
# include "libft.h"
# include <stdio.h> /* TODO: Delete before finish project */
# include <SDL.h>
# include <pthread.h>

# define TITLE "RTV1"
# define WIDTH 640
# define HEIGHT 480
# define ASP_RATIO (double)WIDTH / (double)HEIGHT
# define HWIDTH ((double)WIDTH*0.5f)
# define HHEIGHT ((double)HEIGHT*0.5f)
# define SDL_WINDOW_ARGS TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0
# define SURFACE_LEN WIDTH * HEIGHT * 4
# define BLACK color_new(0, 0, 0)
# define WHITE color_new(255, 255, 255)
# define GREY color_new(128, 128, 128)
# define RED color_new(255, 0, 0)
# define GREEN color_new(0, 255, 0)
# define BLUE color_new(0, 0, 255)
# define PINK color_new(255, 182, 193)
# define BROWN color_new(139, 69, 19)

# define COUNT_SPHERE 0
# define COUNT_CONE 1
# define COUNT_PLANES 2
# define COUNT_CYLINDER 3
# define COUNT_LIGHT 4

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
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct	s_ray
{
	t_vec		o;
	t_vec		d;
	t_vec		point_at;
}				t_ray;

typedef struct	s_material
{
	t_color		c;
	double		a0;
	double		a1;
	double 		exp;
}				t_material;

typedef struct	s_hit
{
	t_vec		p;
	t_vec		n;
	double 		d;
	t_material	m;
	int 		collided;
	double 		diffuse;
	double		specular;
}				t_hit;

typedef struct	s_sphere
{
	t_vec		pos;
	double		rad;
	t_material	mat;
}				t_sphere;

typedef struct	s_plane
{
	t_vec		pos;
	t_vec		rot;
	t_vec		axis;
	t_material	mat;
}				t_plane;

typedef struct	s_cone
{
	t_vec		pos;
	t_vec		axis;
	t_vec		rot;
	double		angle;
	t_material	mat;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec		pos;
	t_vec		axis;
	t_vec		rot;
	double 		rad;
	double 		height;
	t_material	mat;
}				t_cylinder;

typedef struct	s_light
{
	t_vec		position;
	t_vec		direction;
	double		intensity;
	t_material	mat;
}				t_light;

typedef struct	s_camera
{
	t_vec		position;
	t_vec		dir;
	t_vec		right;
	t_vec		down;
	t_vec		rotation;
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
	t_cone		*cones;
	t_plane		*planes;
	t_cylinder	*cylinders;
	int 		counts[5];
	t_light		*light;
	t_camera	camera;
}				t_scene;

typedef struct	s_app
{
	t_sdl		*sdl;
	const Uint8	*keys;
	t_scene		*scene;
	double 		fov;
	double 		asp_rat;
	t_vec		pos;
	t_vec		rot;
	int 		redraw;
}				t_app;

typedef struct	s_thread_data
{
	pthread_t 		tr;
	t_app			*app;
	int 			scene_id;
	int 			sx;
	int 			ex;
	int 			sy;
	int 			ey;
}				t_thread_data;

void		set_pixel(SDL_Surface *surface, int x, int y, t_color c);
t_color		get_pixel(SDL_Surface *surface, int x, int y);

double 		vec_length(t_vec v);
t_vec		vec_normalize(t_vec v);
double		vec_dot(t_vec v1, t_vec v2);
t_vec		vec_cross(t_vec v1, t_vec v2);
t_vec		vec_add(t_vec v1, t_vec v2);
t_vec		vec_new(double x, double y, double z);
t_vec		vec_sub(t_vec v1, t_vec v2);
t_vec		vec_mul_by(t_vec v, double k);
t_vec		vec_div_by(t_vec v, double k);
t_vec		vec_invert(t_vec v);
t_vec		vec_point_at(t_ray ray, double length);
void		vec_add_ptr(t_vec *ov, t_vec v2);
void		vec_sub_ptr(t_vec *ov, t_vec v2);
void		vec_mul_by_ptr(t_vec *ov, double k);
void		vec_div_by_ptr(t_vec *ov, double k);

void		color_set(t_color *c, int r, int g, int b);
t_color		color_new(int r, int g, int b);
t_color 	color_add(t_color c, double k);
t_color		color_sum(t_color c1, t_color c2);
t_color		color_mul(t_color c1, t_color c2);
t_color		color_mul_by(t_color c, double k);
t_color		color_mix(t_color c1, t_color c2, double amount);
void		color_clamp(t_color *c);

void		set_camera(t_camera *camera, t_vec pos, t_vec look_at);

t_vec		ray_direction(t_app *app, int x, int y);

int			event_handling(t_app *app);

void		trace_rays(t_app *app, int scene_id);

double		sphere_intersection(t_ray ray, t_sphere sphere);
t_vec		sphere_normal(t_vec center, t_vec p);
t_sphere	sphere_new(t_vec pos, double rad, t_material mat);
void		check_spheres(t_scene scene, t_ray ray, t_hit *hit);

double		plane_intersection(t_ray ray, t_plane plane);
t_plane		plane_new(t_vec pos, t_vec rot, t_material mat);
void		check_planes(t_scene scene, t_ray ray, t_hit *hit);

t_cone		cone_new(t_vec pos, t_vec rot, double angle, t_material material);
void		check_cone(t_scene scene, t_ray ray, t_hit *hit);

t_light		light_new(t_vec position, double intensity);
void		process_lights(t_scene scene, t_ray ray, t_hit *hit);

t_cylinder	cylinder_new(t_vec pos, t_vec rot, double rad, t_material mat);
double		cylinder_intersection(t_ray ray, t_cylinder	obj);
t_vec		cylinder_normal(t_ray ray, t_hit hit, t_cylinder obj);
void		check_cylinder(t_scene scene, t_ray ray, t_hit *hit);

double		calc_abc(double a, double b, double c);
void		set_axis(t_vec *axis, t_vec rot);
t_material	mat_new(double a_0, double a_1, double exp, t_color color);
#endif
