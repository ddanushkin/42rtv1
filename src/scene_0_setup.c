/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_0_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:52 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:52 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_0_set_spheres(t_scene *scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_spheres(scene, 3);
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(-1.2, 0.0, 0.0),
			0.5,
			mat_new(0.8, 1.8, 10, RED));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(0.0, 0.0, 0.0),
			0.6,
			mat_new(0.8, 1.8, 10, GREEN));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(1.2, 0.0, 0.0),
			0.5,
			mat_new(0.8, 1.8, 10, BLUE));
}

void	scene_0_set_cones(t_scene *scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_cones(scene, 4);
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			40.0,
			mat_new(0.8, 0.8, 10, GREY));
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(-3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			40.0,
			mat_new(0.8, 0.8, 10, GREY));
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(0, 0.0, 0.0),
			vec_new(0.0, 0.0, 45.0),
			15.0,
			mat_new(1.0, 1.0, 10, PINK));
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(0, 0.0, 0.0),
			vec_new(0.0, 0.0, -45.0),
			15.0,
			mat_new(1.0, 1.0, 10, PINK));
}

void	scene_0_set_planes(t_scene *scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_planes(scene, 2);
	scene->planes[c[PLANE_OBJ]++] = plane_new(
			vec_new(0.0, -3.0, 0.0),
			vec_new(0.0, 0.0, 0.0),
			mat_new(0.8, 0.8, 10, WHITE));
	scene->planes[c[PLANE_OBJ]++] = plane_new(
			vec_new(0.0, 0.0, -10.0),
			vec_new(90.0, 0.0, 0.0),
			mat_new(0.8, 0.8, 10, WHITE));
}

void	scene_0_set_cylinders(t_scene *scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_cylinders(scene, 2);
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			1.5,
			mat_new(0.8, 0.8, 15, ORANGE));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(-3.0, 2.0, -2.5),
			vec_new(0.0, 0.0, 0.0),
			1.5,
			mat_new(0.8, 0.8, 15, ORANGE));
}

void	init_scene_0(t_app *app)
{
	int		*c;
	t_scene	*scene;

	scene = &app->scenes[0];
	c = &scene->counts[0];
	ft_memset(&scene->counts, 0, sizeof(int[5]));
	scene_0_set_planes(scene);
	scene_0_set_spheres(scene);
	scene_0_set_cylinders(scene);
	scene_0_set_cones(scene);
	scene_add_lights(scene, 4);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(-1.2, 0.0, 5.0),
			100);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(1.2, 0.0, 5.0),
			100);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.0, 5.0, 10.0),
			100);
}
