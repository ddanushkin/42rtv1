/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglover <lglover@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:28:22 by lglover           #+#    #+#             */
/*   Updated: 2019/10/09 10:28:29 by lglover          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "math.h"
# include "libft.h"
# include <SDL.h>
# include <pthread.h>

# define TITLE "RTV1"
# define WIDTH 512
# define HEIGHT 512

# define POS_SPEED 1.0
# define ROT_SPEED 2.0

# define BLACK color_new(0, 0, 0)
# define WHITE color_new(255, 255, 255)
# define GREY color_new(128, 128, 128)
# define RED color_new(255, 0, 0)
# define GREEN color_new(0, 255, 0)
# define BLUE color_new(0, 0, 255)
# define CYAN color_new(0, 255, 255)
# define PINK color_new(255, 0, 127)
# define BROWN color_new(153, 76, 0)
# define ORANGE color_new(255, 128, 0)

# define PALETTE_C1 color_new(198, 65, 145)
# define PALETTE_C2 color_new(0, 191, 178)
# define PALETTE_C3 color_new(240, 243, 189)
# define PALETTE_C4 color_new(2, 127, 144)
# define PALETTE_C5 color_new(26, 94, 99)

# define SPHERE_OBJ 0
# define CONE_OBJ 1
# define PLANE_OBJ 2
# define CYLINDER_OBJ 3
# define LIGHT_OBJ 4

# define TRUE 1
# define FALSE 0

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
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
}				t_ray;

typedef struct	s_material
{
	t_color		c;
	double		a0;
	double		a1;
	double		exp;
}				t_material;

typedef struct	s_hit
{
	t_vec		p;
	t_vec		n;
	double		d;
	t_material	m;
	int			collided;
	double		diffuse;
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
	double		rad;
	t_material	mat;
}				t_cylinder;

typedef struct	s_light
{
	t_vec		position;
	double		intensity;
}				t_light;

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
	int			counts[5];
	t_light		*lights;
}				t_scene;

typedef struct	s_app
{
	t_sdl		*sdl;
	const Uint8	*keys;
	t_scene		*scenes;
	double		fov;
	double		asp_rat;
	t_vec		pos;
	t_vec		rot;
}				t_app;

typedef struct	s_thread_data
{
	pthread_t	tr;
	t_app		*app;
	int			sx;
	int			ex;
	int			sy;
	int			ey;
}				t_thread_data;

void			safe_quit(t_app *app);

void			set_pixel(SDL_Surface *surface, int x, int y, t_color c);

double			vec_length(t_vec v);
t_vec			vec_normalize(t_vec v);
double			vec_dot(t_vec v1, t_vec v2);
t_vec			vec_add(t_vec v1, t_vec v2);
t_vec			vec_new(double x, double y, double z);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_mul_by(t_vec v, double k);
t_vec			vec_invert(t_vec v);
t_vec			vec_point_at(t_ray ray, double length);

t_color			color_new(int r, int g, int b);
t_color			color_sum(t_color c1, t_color c2);
t_color			color_mul_by(t_color c, double k);
void			color_clamp(t_color *c);

void			init_app(t_app *app);
int				init_sdl(t_app *app);

void			app_set_camera(t_app *app, t_vec pos, t_vec rot);

t_vec			ray_direction(t_app *app, int x, int y);
void			read_config(t_app *app, char *path);
int				num_elem(char **tab);

int				event_handling(t_app *app);

void			trace_rays(t_app *app);

void			event_redraw(t_app *app, const uint8_t *keys);
void			event_move(const uint8_t *keys, t_vec *pos);
void			event_rotate(const uint8_t *keys, t_vec *rot);

double			sphere_intersection(t_ray ray, t_sphere sphere);
t_vec			sphere_normal(t_vec center, t_vec p);
t_sphere		sphere_new(t_vec pos, double rad);
void			check_spheres(t_scene scene, t_ray ray, t_hit *hit);

double			plane_intersection(t_ray ray, t_plane plane);
t_plane			plane_new(t_vec pos, t_vec rot);
void			check_planes(t_scene scene, t_ray ray, t_hit *hit);

t_cone			cone_new(t_vec pos, t_vec rot, double angle);
void			check_cone(t_scene scene, t_ray ray, t_hit *hit);

t_light			light_new(t_vec position, double intensity);
void			process_lights(t_scene scene, t_ray ray, t_hit *hit);

t_cylinder		cylinder_new(t_vec pos, t_vec rot, double rad);
double			cylinder_intersection(t_ray ray, t_cylinder	obj);
t_vec			cylinder_normal(t_ray ray, t_hit hit, t_cylinder obj);
void			check_cylinder(t_scene scene, t_ray ray, t_hit *hit);

void			scene_add_planes(t_scene *scene, int number);
void			scene_add_spheres(t_scene *scene, int number);
void			scene_add_cones(t_scene *scene, int number);
void			scene_add_cylinders(t_scene *scene, int number);
void			scene_add_lights(t_scene *scene, int number);

void			scene_set_sphere(t_scene *scene, t_vec position,
								double radius);
void			scene_set_cone(t_scene *scene, t_vec position,
								t_vec rotation, double angle);
void			scene_set_cylinder(t_scene *scene, t_vec position,
								t_vec rotation, double radius);
void			scene_set_plane(t_scene *scene, t_vec position,
								t_vec rotation);
void			scene_set_light(t_scene *scene, t_vec position,
								double intensity);

double			calc_abc(double a, double b, double c);
void			set_axis(t_vec *axis, t_vec rot);
void			set_view(t_vec *axis, t_vec rot);
t_material		mat_new(double a_0, double a_1, double exp, t_color color);
#endif
