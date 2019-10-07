/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_4_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:48 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:48 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_4_set_cylinders(t_scene *scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_cylinders(scene, 8);
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(10, 5, -1),
			vec_new(0, 0, 90),
			1,
			mat_new(1, 0, 10, CYAN));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(0, 0, -2),
			vec_new(0, 0, 45),
			0.2,
			mat_new(1, 0, 10, RED));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(0, 0, -3),
			vec_new(0, 0, -45),
			0.2,
			mat_new(1, 0, 10, GREEN));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(0, 0, -4),
			vec_new(0, 0, 0),
			0.2,
			mat_new(1, 0, 10, BLUE));
}

void	scene_4_set_lights(t_scene *scene)
{
	int		*c;

	scene_add_lights(scene, 3);
	c = &scene->counts[0];
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.0, 3.0, 10.0),
			100);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(2, 0, -2.0),
			100);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.5, -2.0, 10.0),
			1000);
}

void	init_scene_4(t_app *app)
{
	int		*c;
	t_scene	*scene;

	scene = &app->scenes[4];
	c = &scene->counts[0];
	ft_memset(&scene->counts, 0, sizeof(int[5]));
	scene_4_set_cylinders(scene);
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(-10, 0, -10),
			vec_new(0, 0, 0),
			5,
			mat_new(1, 0, 10, PINK));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(10, 0, -10),
			vec_new(0, 0, 0),
			5,
			mat_new(1, 0, 10, PINK));
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			vec_new(10, -5, -1),
			vec_new(0, 0, 90),
			1,
			mat_new(1, 0, 10, CYAN));
}
