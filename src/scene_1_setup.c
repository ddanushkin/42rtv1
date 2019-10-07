/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_1_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:51 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:51 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_1_set_spheres(t_scene	*scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_spheres(scene, 5);
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(0, 0, 0),
			0.5,
			mat_new(1, 0, 10, PINK));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(-3.5, 0, 0),
			1.5,
			mat_new(1, 1, 10, ORANGE));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(3.5, 0, 0),
			2.5,
			mat_new(1, 1, 10, CYAN));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(-5.5, -2, -1),
			2.5,
			mat_new(1, 1, 10, GREEN));
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			vec_new(0, 0, -11),
			10.5,
			mat_new(1, 1, 10, RED));
}

void	init_scene_1(t_app *app)
{
	int		*c;
	t_scene	*scene;

	scene = &app->scenes[1];
	c = &scene->counts[0];
	ft_memset(&scene->counts, 0, sizeof(int[5]));
	scene_1_set_spheres(scene);
	scene_add_lights(scene, 3);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.0, 3.0, 1.0),
			20);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.5, -2.0, 3.0),
			100);
}