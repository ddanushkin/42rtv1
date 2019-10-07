/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:49 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:49 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_3_set_planes(t_scene	*scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_planes(scene, 4);
	scene->planes[c[PLANE_OBJ]++] = plane_new(
			vec_new(0, -5, 0),
			vec_new(0, 0, 0),
			mat_new(1, 1, 10, RED));
	scene->planes[c[PLANE_OBJ]++] = plane_new(
			vec_new(0, 0, -5),
			vec_new(90, 0, 0),
			mat_new(1, 1, 10, GREEN));
	scene->planes[c[PLANE_OBJ]++] = plane_new(
			vec_new(-10, 0, -5),
			vec_new(90, 90, 0),
			mat_new(1, 1, 10, BLUE));
	scene->planes[c[PLANE_OBJ]++] = plane_new(
			vec_new(10, 0, -5),
			vec_new(90, -90, 0),
			mat_new(1, 1, 10, ORANGE));
}

void	init_scene_3(t_app *app)
{
	int		*c;
	t_scene	*scene;

	scene = &app->scenes[3];
	c = &scene->counts[0];
	ft_memset(&scene->counts, 0, sizeof(int[5]));
	scene_3_set_planes(scene);
	scene_add_lights(scene, 4);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(-8.0, 0.0, 0.0),
			50);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(8.0, 0.0, 0.0),
			50);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0, 10.5, -3.0),
			50);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0, -3.0, -3.0),
			150);
}