/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_2_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:50 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:50 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_2_set_cones(t_scene	*scene)
{
	int		*c;

	c = &scene->counts[0];
	scene_add_cones(scene, 6);
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(-3.0, 2.5, -2.5),
			vec_new(0.0, 0.0, 0.0),
			15.0,
			mat_new(0.8, 0.8, 10, GREY));
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(3.0, -2.5, -2.5),
			vec_new(0.0, 0.0, 0.0),
			15.0,
			mat_new(0.8, 0.8, 10, GREY));
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(0, 0.0, 0.0),
			vec_new(0.0, 0.0, 45.0),
			5.0,
			mat_new(1.0, 1.0, 10, PINK));
	scene->cones[c[CONE_OBJ]++] = cone_new(
			vec_new(0, 0.0, 0.0),
			vec_new(0.0, 0.0, -45.0),
			5.0,
			mat_new(1.0, 1.0, 10, PINK));
}

void	init_scene_2(t_app *app)
{
	int		*c;
	t_scene	*scene;

	scene = &app->scenes[2];
	c = &scene->counts[0];
	ft_memset(&scene->counts, 0, sizeof(int[5]));
	scene_2_set_cones(scene);
	scene_add_lights(scene, 3);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.0, 3.0, 1.0),
			20);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(0.5, -2.0, 3.0),
			100);
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			vec_new(-1.5, 2.0, 3.0),
			100);
}
